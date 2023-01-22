/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:54:59 by alilin            #+#    #+#             */
/*   Updated: 2023/01/22 15:26:23 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	sig_handler(int sig) {
	if (sig == SIGINT)
	{
		env->signals.end = 1;
		// get_statistic();
	}
	// if (sig == SIGALRM)
	// 	env->signals.send = 1;
	return;
}

void	init_params()
{
	if (!(env = malloc(sizeof(t_ping_env))))
        	print_error("Error: malloc failed\n");   
	ft_bzero(env, sizeof(t_ping_env));
	env->ttl = 255;
	env->interval = 1;
	
	env->pkt.ip = (struct iphdr *)env->pkt.hdr_buf;
	env->pkt.hdr = (struct icmphdr *)(env->pkt.ip + 1);
	env->pid = getpid();
	env->seq = 1;
    
	// env->sent = 0;
	env->sent_pkt_count = 0;
    
	env->rtt = 0;
	env->min = 0.0;
	env->max = 0.0;
	env->cumul = 0;
	env->avg = 0;
    
	// env->receive = 0;
	env->bytes = 0;
	env->received_pkt_count = 0;
	env->signals.send = 1;
	env->signals.end = 0;
	// env->timeout_flag = false;
}

void	dns_lookup(char **av)
{
	int		i;

	i = 1;
	while(av[i])
	{
		if (av[i][1] != '-')
		{
			ft_bzero(&(env->hints), sizeof(env->hints));
			env->hints.ai_family = AF_INET;
			env->hints.ai_socktype = SOCK_RAW;
			env->hints.ai_protocol = IPPROTO_ICMP;
			if (getaddrinfo(av[i], NULL, &(env->hints), &(env->res)) != 0)
				print_error("ping: %s: Name or service not known\n");
			env->hostname_dst = av[i];
			env->sa_in = (struct sockaddr_in *)env->res->ai_addr;
			inet_ntop(AF_INET, (void *)&(env->sa_in->sin_addr), env->host_dst, INET6_ADDRSTRLEN);
		}
		i++;
	}
	return;
}

void	set_socket()
{
	int		sock_fd;
	int		yes;
	// struct timeval	timeout;

	// timeout.tv_sec = 5;
	// timeout.tv_usec = 0;
	yes = 1;
	sock_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sock_fd < 0)
		print_error("Error: socket opening failed\n");
	if (setsockopt(sock_fd, IPPROTO_IP, IP_HDRINCL, &yes, sizeof(yes)) < 0)
		print_error("Error: setsockopt failed\n");
	// if (setsockopt(sock_fd, IPPROTO_IP, IP_TTL, &(env->ttl), sizeof(env->ttl)) == -1)
	// 	print_error("Error: setsockopt failed\n");
	// if (setsockopt(sock_fd, IPPROTO_IP, IP_RECVTTL, &yes, sizeof(yes)) == -1)
		// print_error("Error: setsockopt failed\n");
	// if ((setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, (const void *)&timeout, sizeof(timeout))) == -1)
		// print_error("Error: setsockopt failed\n");
	env->sockfd = sock_fd;
}

void    configure_send()
{  
	ft_bzero((void *)env->pkt.hdr_buf, PACKET_SIZE);
	env->pkt.ip->version = 4;
	env->pkt.ip->ihl = sizeof(*(env->pkt.ip)) >> 2;
	env->pkt.ip->ttl = env->ttl;
	env->pkt.ip->protocol = IPPROTO_ICMP;
	inet_pton(AF_INET, env->host_dst, &(env->pkt.ip->daddr));
	// env->daddr = env->pkt.ip->daddr;
	// ft_memset(&(env->hdr_buf), 0, sizeof(env->hdr_buf));
	// env->hdr = (struct icmp *)env->hdr_buf;
	env->pkt.hdr->type = ICMP_ECHO; // icmp_type under mac and type under linux
	env->pkt.hdr->code = 0; // icmp_code under mac and code under linux
	env->pkt.hdr->un.echo.id = env->pid; // icmp_hun.ih_idseq.icd_id under mac and un.echo.id
	env->pkt.hdr->un.echo.sequence = env->seq++; // icmp_hun.ih_idseq.icd_seq under mac and un.echo.sequence under linux
	env->pkt.hdr->checksum = checksum((unsigned short *)(env->pkt.hdr), sizeof(struct icmphdr)); // icmp_cksum under mac and checksum under linux
}

void	send_packet()
{
	configure_send();
	if (sendto(env->sockfd, (void *)&env->pkt, PACKET_SIZE, 0, (void *)env->sa_in, sizeof(struct sockaddr_in)) < 0)
		print_error("Error: sendto failed\n");
	if (gettimeofday(&env->s, NULL) < 0)
		print_error("Error: gettimeofday failed\n");
	env->sent_pkt_count++;
	env->signals.send = 0;
}

void    configure_receive()
{
	t_res		*ret;

	ret = &env->response;
	ft_bzero((void *)env->pkt.hdr_buf, PACKET_SIZE);
	ft_bzero(ret, sizeof(t_res));
	ret->iov->iov_base = (void *)env->pkt.hdr_buf;
	ret->iov->iov_len = sizeof(env->pkt.hdr_buf);
	ret->ret_hdr.msg_name = NULL;
	ret->ret_hdr.msg_namelen = 0;
	ret->ret_hdr.msg_iov = ret->iov;
	ret->ret_hdr.msg_iovlen = 1;
	ret->ret_hdr.msg_flags = MSG_DONTWAIT;
}

void	get_packet(void)
{
	int		ret;

	configure_receive();
	while (!env->signals.end)
	{
		ret = recvmsg(env->sockfd, &env->response.ret_hdr, MSG_DONTWAIT);
		if (ret > 0)
		{
			env->bytes = ret;
			if (env->pkt.hdr->un.echo.id == env->pid)
			{
				printf("ttl = %d\n", env->pkt.ip->ttl);
				// calc_rtt();
				// printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.2Lf ms\n",
				// g_params->bytes - (int)sizeof(struct iphdr), g_params->addrstr,
				// g_params->pckt.hdr->un.echo.sequence, g_params->pckt.ip->ttl,
				// g_params->time.rtt);
			}
			// else if (g_params->flags & FLAG_V)
			// 	printf_v();
			return ;
		}
	}
}

void	ping_loop()
{
	set_socket();
	configure_send();
	printf("PING %s (%s) %d(%d) bytes of data.\n", env->hostname_dst, env->host_dst, 56, 84);
	if (gettimeofday(&env->start, NULL) < 0)
		print_error("Error: gettimeofday failed\n");
	while (!env->signals.end)
	{
		if (env->signals.send)
		{
			send_packet();
			alarm(1);
			get_packet();
		}
	}
    // gettimeofday(&tv_start, NULL);
    // while(g_ping_loop == true)
    // {
        // if ((env->sent = sendto(env->sockfd, &(env->pkt), PACKET_SIZE, 0, (struct sockaddr *)env->res->ai_addr, sizeof(struct sockaddr))) < 0)
        //     print_error("Error: sendto failed\n");
        // if (env->sent >= 0)
        // {
        //     env->sent_pkt_count++;
        //     configure_receive();
        //     while (1)
        //     {
        //         env->receive = recvmsg(env->sockfd, &(env->response.ret_hdr), MSG_DONTWAIT);
        //         if (env->receive > 0)
        //         {
        //             if (env->pkt.hdr->icmp_hun.ih_idseq.icd_id == env->pid)
        //             {
        //                 printf("ttl=%d\n", env->pkt.ip->ip_ttl);
        //             }
        //             return;
        //         }
                
        //     }
            // printf("%d\n", env->receive);
            // if (env->receive > 0) {
            //     struct cmsghdr *cmsg;
            //     int *ttlptr = NULL;
            //     for (cmsg = CMSG_FIRSTHDR(&(env->ret_hdr)); cmsg != NULL; cmsg = CMSG_NXTHDR(&(env->ret_hdr),cmsg))
            //     {
            //         if ((cmsg->cmsg_level == IPPROTO_IP) && (cmsg->cmsg_type == IP_TTL) && (cmsg->cmsg_len))
            //         {
            //             ttlptr = (int *) CMSG_DATA(cmsg);
            //             env->ret_ttl = *ttlptr;
            //             printf("received_ttl = %d \n", env->ret_ttl);
            //             break;
            //         }
            //     }
            // }
        // }
        // usleep(env->interval);
    // // }    
}

int	main(int ac, char  **av) {
	t_options	opt;
	if (getuid() != 0)
		print_error("error: Operation not permitted\n");
	if (ac < 2)
		print_error("usage error: Destination address required\n");
	char		*option;
	char		*options[] = {
		"h",
		"v",
		NULL
	};
	option = ft_getopt(av, options);
	ft_handleopt(&opt, option);
	free(option);
	init_params();
	dns_lookup(av);
	ping_loop();
	signal(SIGALRM, sig_handler);
	signal(SIGINT, sig_handler);
	return (0);
}
