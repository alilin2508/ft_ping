/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_send_and_receive.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:13:20 by alilin            #+#    #+#             */
/*   Updated: 2023/02/09 16:51:45 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void    configure_send(t_ping_env *env)
{
	ft_bzero((void *)env->pkt.hdr_buf, PACKET_SIZE);
	env->pkt.ip->version = 4;
	env->pkt.ip->ihl = sizeof(*(env->pkt.ip)) >> 2;
	env->pkt.ip->ttl = env->ttl;
	env->pkt.ip->protocol = IPPROTO_ICMP;
	inet_pton(AF_INET, env->host_dst, &(env->pkt.ip->daddr));
	env->pkt.hdr->type = ICMP_ECHO; // icmp_type under mac and type under linux
	env->pkt.hdr->code = 0; // icmp_code under mac and code under linux
	env->pkt.hdr->un.echo.id = env->pid; // icmp_hun.ih_idseq.icd_id under mac and un.echo.id
	env->pkt.hdr->un.echo.sequence = env->seq++; // icmp_hun.ih_idseq.icd_seq under mac and un.echo.sequence under linux
	env->pkt.hdr->checksum = checksum((unsigned short*)env->pkt.hdr, sizeof(struct icmphdr)); // icmp_cksum under mac and checksum under linux
}


void    configure_receive(t_ping_env *env)
{
	ft_bzero((void *)&env->response.ret_hdr, sizeof(env->response.ret_hdr));
	ft_bzero((void *)env->pkt.hdr_buf, PACKET_SIZE);
	env->response.iov->iov_base = (void *)env->pkt.hdr_buf;
	env->response.iov->iov_len = sizeof(env->pkt.hdr_buf);
	env->response.ret_hdr.msg_name = NULL;
	env->response.ret_hdr.msg_namelen = 0;
	env->response.ret_hdr.msg_iov = env->response.iov;
	env->response.ret_hdr.msg_iovlen = 1;
	env->response.ret_hdr.msg_flags = MSG_DONTWAIT;
}

void	send_packet(t_ping_env *env)
{
	configure_send(env);
	if (sendto(env->sockfd, (void *)&env->pkt, PACKET_SIZE, 0, env->res->ai_addr, env->res->ai_addrlen) < 0)
		print_error("Error: sendto failed\n");
	if (gettimeofday(&env->s, NULL) < 0)
		print_error("Error: gettimeofday failed\n");
	env->sent_pkt_count++;
}

void	get_packet(t_ping_env *env)
{
	int		ret;

	configure_receive(env);
	ret = recvmsg(env->sockfd, &env->response.ret_hdr, 0);
	if (ret > 0)
	{
		env->bytes = ret;
		if ((env->pkt.hdr->un.echo.id == env->pid) && (env->pkt.hdr->un.echo.sequence != env->seq))
		{
            if (gettimeofday(&env->r, NULL) < 0)
		        print_error("Error: gettimeofday failed\n");
            env->received_pkt_count++;
			calc_rtt(env);
			if ((ft_strlen(env->hostname_dst) == ft_strlen(env->host_dst)) && (!ft_strncmp(env->hostname_dst, env->host_dst, ft_strlen(env->host_dst))))
				printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.2Lf ms\n", env->bytes, env->host_dst, env->pkt.hdr->un.echo.sequence, env->pkt.ip->ttl, env->rtt);
			else
            	printf("%d bytes from %s (%s): icmp_seq=%d ttl=%d time=%.2Lf ms\n", env->bytes, env->hostname_dst, env->host_dst, env->pkt.hdr->un.echo.sequence, env->pkt.ip->ttl, env->rtt);
		}
		else if (env->pkt.hdr->type == 11 && env->pkt.hdr->code == 0)
			print_ttl(env);
		else if (env->pkt.hdr->type != 11 && env->pkt.hdr->code != 0)
			print_verbose(env);
		return ;
	}
}