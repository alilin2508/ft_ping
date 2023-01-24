/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:54:59 by alilin            #+#    #+#             */
/*   Updated: 2023/01/24 16:46:27 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

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