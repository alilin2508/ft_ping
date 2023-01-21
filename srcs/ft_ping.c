/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:54:59 by alilin            #+#    #+#             */
/*   Updated: 2023/01/21 13:49:54 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void int_handler(int sig) {
    if (sig == SIGINT)
        g_ping_loop = false;
    return;
}

void dns_lookup(t_ping_env *env, char **av)
{
    int i;
    int ret;

    i = 1;
    while(av[i])
    {
        if (av[i][1] != '-')
        {
            ft_memset(&(env->hints), 0, sizeof(struct addrinfo));
            env->hints.ai_family = AF_INET;
            env->hints.ai_socktype = SOCK_RAW;
            env->hints.ai_protocol = IPPROTO_ICMP;
            ret = getaddrinfo(av[i], NULL, &(env->hints), &(env->res));
            if (ret != 0)
            {
                fprintf(stderr, "ping: %s: Name or service not known\n%s", av[i], gai_strerror(ret));
                exit(EXIT_FAILURE);
            }
            env->hostname_dst = av[i];
        }
        i++;
    }
    return;
}

void set_socket(t_ping_env *env)
{
    int yes;
    struct timeval	timeout;

	timeout.tv_sec = 2;
	timeout.tv_usec = 0;
    yes = 1;
    env->sockfd = socket(env->res->ai_family, env->res->ai_socktype, env->res->ai_protocol);
    if (env->sockfd < 0)
        print_error("Error: socket opening failed\n");
    env->ttl = 255;
    if (setsockopt(env->sockfd, IPPROTO_IP, IP_TTL, &(env->ttl), sizeof(env->ttl)) == -1)
        print_error("Error: setsockopt failed\n");
    if (setsockopt(env->sockfd, IPPROTO_IP, IP_RECVTTL, &yes, sizeof(yes)) == -1)
        print_error("Error: setsockopt failed\n");
    if ((setsockopt(env->sockfd, SOL_SOCKET, SO_RCVTIMEO, (const void *)&timeout, sizeof(timeout))) == -1)
		print_error("Error: setsockopt failed\n");
}

void    configure_send(t_ping_env *env)
{
    struct sockaddr_in	*sa_in;
    char                *ip_share;

    sa_in = (struct sockaddr_in *)env->res->ai_addr;
    if ((ip_share = malloc(INET_ADDRSTRLEN)) < 0)
		print_error("Error: malloc failed\n");
	inet_ntop(AF_INET, &(sa_in->sin_addr), ip_share, INET_ADDRSTRLEN);
    env->host_dst = ip_share;
    free(ip_share);
    
    env->sent = 0;
    ft_memset(&(env->hdr_buf), 0, sizeof(env->hdr_buf));
    env->hdr = (struct icmp *)env->hdr_buf;
    env->hdr->icmp_type = ICMP_ECHO; // icmp_type under mac and type under linux
    env->hdr->icmp_code = 0; // icmp_code under mac and code under linux
    env->hdr->icmp_cksum = calculate_checksum((unsigned short *)(env->hdr), sizeof(env->hdr)); // icmp_cksum under mac and checksum under linux
    env->hdr->icmp_hun.ih_idseq.icd_id = env->pid; // icmp_hun.ih_idseq.icd_id under mac and un.echo.id
    env->hdr->icmp_hun.ih_idseq.icd_seq = env->sent_pkt_count++; // icmp_hun.ih_idseq.icd_seq under mac and un.echo.sequence under linux
}

void    configure_receive(t_ping_env *env)
{
    env->receive = 0;
    ft_memset(&(env->buf), 0, sizeof(env->buf));
    env->iov.iov_base = env->buf;
	env->iov.iov_len = sizeof(env->buf);
    ft_memset(&(env->ret_hdr), '\0', sizeof(env->ret_hdr));
    env->ret_hdr.msg_name = env->res->ai_addr;
    env->ret_hdr.msg_namelen = sizeof(*env->res->ai_addr);
	env->ret_hdr.msg_iov = &env->iov;
	env->ret_hdr.msg_iovlen = 1;
	env->ret_hdr.msg_control = &env->retbuf;
	env->ret_hdr.msg_controllen = sizeof(env->retbuf);
	env->ret_hdr.msg_flags = 0;
}

void ping_loop(t_ping_env *env)
{
    // struct timeval	tv_start, tv_end;
    env->timeout = 1;
    env->interval = 5;

    env->min = -1;
    env->max = 0;
    env->cumul = 0;
    
    env->sent = 0;
    env->sent_pkt_count = 0;
    env->receive = 0;
    env->received_pkt_count = 0;
    env->timeout_flag = false;
    g_ping_loop = true;
    
    configure_send(env);
    // display first line info !!!! TO DO
    // gettimeofday(&tv_start, NULL);
    // while(g_ping_loop == true)
    // {
        if ((env->sent = sendto(env->sockfd, &(env->hdr_buf), sizeof(env->hdr_buf), 0, (struct sockaddr *)env->res->ai_addr, sizeof(*env->res->ai_addr))) < 0)
            print_error("Error: sendto failed\n");
        if (env->sent >= 0)
        {
            env->sent_pkt_count++;
            configure_receive(env);
            env->receive = recvmsg(env->sockfd, &(env->ret_hdr), MSG_TRUNC);
            printf("%d\n", env->receive);
            if (env->receive > 0) {
                struct cmsghdr *cmsg;
                int *ttlptr = NULL;
                for (cmsg = CMSG_FIRSTHDR(&(env->ret_hdr)); cmsg != NULL; cmsg = CMSG_NXTHDR(&(env->ret_hdr),cmsg))
                {
                    if ((cmsg->cmsg_level == IPPROTO_IP) && (cmsg->cmsg_type == IP_TTL) && (cmsg->cmsg_len))
                    {
                        ttlptr = (int *) CMSG_DATA(cmsg);
                        env->ret_ttl = *ttlptr;
                        printf("received_ttl = %d \n", env->ret_ttl);
                        break;
                    }
                }
            }
        }
        usleep(env->interval);
    // }    
}

int main(int ac, char  **av) {
    t_ping_env env;
    t_options  opt;

    if (ac < 2) {
        print_error("usage error: Destination address required\n");
    }
    char        *option;
    char        *options[] = {
        "h",
        "v",
        NULL
    };
    option = ft_getopt(av, options);
    ft_handleopt(&opt, option);
    free(option);
    dns_lookup(&env, av);
    set_socket(&env);
    env.pid = getpid();
    ping_loop(&env);
    signal(SIGINT, int_handler);
    return (0);
}