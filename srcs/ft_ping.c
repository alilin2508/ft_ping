/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:54:59 by alilin            #+#    #+#             */
/*   Updated: 2023/01/24 16:36:37 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void    get_statistic(t_ping_env *env)
{
    if (gettimeofday(&env->end, NULL) < 0)
		print_error("Error: gettimeofday failed\n");
    long double loss;
    long double time;
	long double	mdev;

	mdev = 0.0;
    loss = (((env->sent_pkt_count - env->received_pkt_count) / env->sent_pkt_count) * 100);
	time = (env->end.tv_usec - env->start.tv_usec) / 1000000.0;
	time += (env->end.tv_sec - env->start.tv_sec);
	time *= 1000.0;
	env->avg /= env->received_pkt_count;
	env->rttbuf[env->received_pkt_count] = -1;
	for (int i = 0; env->rttbuf[i] != -1; i++)
	{
		mdev += fabsl(env->rttbuf[i] - env->avg);
	}
	mdev /= env->received_pkt_count;
	free(env->rttbuf);
	
    printf("\n--- %s ping statistics ---\n", env->hostname_dst);
    if (env->error_pkt_count != 0)
        printf("%d packets transmitted, %d received, +%d errors, %.0Lf%% packet loss, time %.0Lfms\n", env->sent_pkt_count, env->received_pkt_count, env->error_pkt_count, loss, time);
    else
	{
        printf("%d packets transmitted, %d received, %.0Lf%% packet loss, time %.0Lfms\n", env->sent_pkt_count, env->received_pkt_count, loss, time);
    	printf("rtt min/avg/max/mdev = %.3Lf/%.3Lf/%.3Lf/%.3Lf ms\n", env->min, env->avg, env->max, mdev);
	}
}

void	sig_handler(int sig)
{
	if (sig == SIGINT) 
	{
		g_send = false;
	}
	return;
}

void	init_params(t_ping_env *env)
{
	env->ttl = 255;
	env->interval = 1;
	
	env->pkt.ip = (struct iphdr *)env->pkt.hdr_buf;
	env->pkt.hdr = (struct icmphdr *)(env->pkt.ip + 1);
	env->pid = getpid();
	env->seq = 1;
    
	env->sent_pkt_count = 0;
    
	env->rtt = 0;
	env->min = 0.0;
	env->max = 0.0;
	env->avg = 0;
    
	env->bytes = 0;
	env->received_pkt_count = 0;
	env->error_pkt_count = 0;
	g_send = true;
}

void	dns_lookup(char **av, t_ping_env *env)
{
	int		i;

	i = 1;
	while(av[i])
	{
		if (av[i][0] != '-')
		{
			ft_bzero(&(env->hints), sizeof(env->hints));
			env->hints.ai_family = AF_INET;
			env->hints.ai_socktype = SOCK_RAW;
			env->hints.ai_protocol = IPPROTO_ICMP;
			if (getaddrinfo(av[i], NULL, &(env->hints), &(env->res)) != 0)
				print_error("ping: %s: Name or service not known\n");
			env->hostname_dst = av[i];
			env->sa_in = (struct sockaddr_in *)env->res->ai_addr;
			inet_ntop(AF_INET, (void *)&(env->sa_in->sin_addr), env->host_dst, INET_ADDRSTRLEN);
		}
		i++;
	}
	return;
}

void	set_socket(t_ping_env *env)
{
	int		sock_fd;
	int		yes;
	struct timeval	timeout;

	timeout.tv_sec = 2;
	timeout.tv_usec = 0;
	yes = 1;
	sock_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if ((sock_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1)
		print_error("Error: socket opening failed\n");
	if (setsockopt(sock_fd, IPPROTO_IP, IP_HDRINCL, &yes, sizeof(yes)) < 0)
		print_error("Error: setsockopt failed\n");
	if ((setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, (const void *)&timeout, sizeof(timeout))) == -1)
		print_error("Error: setsockopt failed\n");
	env->sockfd = sock_fd;
}

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

void	send_packet(t_ping_env *env)
{
	configure_send(env);
	if (sendto(env->sockfd, (void *)&env->pkt, PACKET_SIZE, 0, env->res->ai_addr, env->res->ai_addrlen) < 0)
		print_error("Error: sendto failed\n");
	if (gettimeofday(&env->s, NULL) < 0)
		print_error("Error: gettimeofday failed\n");
	env->sent_pkt_count++;
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

void    calc_rtt(t_ping_env *env)
{
	int			i;
	long double	*tmp;
	
	env->rtt = (env->r.tv_usec - env->s.tv_usec) / 1000000.0;
	env->rtt += (env->r.tv_sec - env->s.tv_sec);
	env->rtt *= 1000.0;
    if (env->rtt > env->max)
        env->max = env->rtt;
    if (env->rtt < env->min || env->min == 0.0)
        env->min = env->rtt;
    env->avg += env->rtt;

	i = 0;
	if (env->received_pkt_count == 1)
	{
		if (!(env->rttbuf = malloc(sizeof(long double) * (env->received_pkt_count + 1))))
			print_error("Error: malloc failed\n");
		env->rttbuf[i] = env->rtt;
		env->rttbuf[i + 1] = -1;
	}
	else
	{
		if (!(tmp = malloc(sizeof(long double) * (env->received_pkt_count + 1))))
			print_error("Error: malloc failed\n");
		for(i = 0; i < env->received_pkt_count; i++)
		{
			tmp[i] = env->rttbuf[i];
		}
		tmp[i] = -1;
		free(env->rttbuf);
		if (!(env->rttbuf = malloc(sizeof(long double) * (env->received_pkt_count + 2))))
			print_error("Error: malloc failed\n");
		for(i = 0; tmp[i] != -1; i++)
		{
			env->rttbuf[i] = tmp[i];
		}
		env->rttbuf[i] = env->rtt;
		env->rttbuf[i + 1] = -1;
		free(tmp);
	}
}

void	print_ttl(t_ping_env *env)
{
	printf("From localhost (172.17.0.1) icmp_seq=%d Time to live exceeded\n", env->sent_pkt_count);
	env->error_pkt_count++;
}

void	print_verbose(t_ping_env *env)
{
	char	str[INET_ADDRSTRLEN];

	printf("%d bytes from %s: type=%d code=%d\n", env->bytes - (int)sizeof(struct iphdr), inet_ntop(AF_INET, (void*)&env->pkt.ip->saddr, str, INET_ADDRSTRLEN), env->pkt.hdr->type, env->pkt.hdr->code);
	env->error_pkt_count++;
}

void	get_packet(t_options *opt, t_ping_env *env)
{
	int		ret;

	configure_receive(env);
	ret = recvmsg(env->sockfd, &env->response.ret_hdr, 0);
	if (ret > 0)
	{
		env->bytes = ret;
		if (env->pkt.hdr->un.echo.id == env->pid)
		{
            if (gettimeofday(&env->r, NULL) < 0)
		        print_error("Error: gettimeofday failed\n");
            env->received_pkt_count++;
			calc_rtt(env);
            printf("%d bytes from %s (%s): icmp_seq=%d ttl=%d time=%.2Lf ms\n", env->bytes, env->hostname_dst, env->host_dst, env->pkt.hdr->un.echo.sequence, env->pkt.ip->ttl, env->rtt);
		}
		else if (env->pkt.hdr->type == 11 && env->pkt.hdr->code == 0)
			print_ttl(env);
		else if (opt->v == true && (env->pkt.hdr->type != 11 && env->pkt.hdr->code != 0))
			print_verbose(env);
		return ;
	}
}

void	ping_loop(t_options *opt, t_ping_env *env)
{
	set_socket(env);
	printf("PING %s (%s) %d(%d) bytes of data.\n", env->hostname_dst, env->host_dst, 56, 84);
	if (gettimeofday(&env->start, NULL) < 0)
		print_error("Error: gettimeofday failed\n");
	while (g_send == true)
	{
		send_packet(env);
		usleep(1000);
		get_packet(opt, env);
		sleep(env->interval);
	}
	get_statistic(env);
}

int	main(int ac, char  **av) {
	t_options	opt;
	t_ping_env	env;
	
	if (getuid() != 0)
		print_error("Error: Operation not permitted\n");
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
	signal(SIGINT, sig_handler);
	init_params(&env);
	dns_lookup(av, &env);
	ping_loop(&opt, &env);
	return (0);
}