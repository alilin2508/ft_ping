/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:54:59 by alilin            #+#    #+#             */
/*   Updated: 2023/01/21 17:20:35 by alilin           ###   ########.fr       */
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
    int                 i;
    int                 ret;
    char                *ip_share;


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
                fprintf(stderr, "ping: %s: Name or service not known\n", av[i]);
                exit(EXIT_FAILURE);
            }
            env->hostname_dst = av[i];
            env->sa_in = (struct sockaddr_in *)env->res->ai_addr;
            if ((ip_share = malloc(INET_ADDRSTRLEN)) < 0)
                print_error("Error: malloc failed\n");
            inet_ntop(AF_INET, &(env->sa_in->sin_addr), ip_share, INET_ADDRSTRLEN);
            env->host_dst = ip_share;
            free(ip_share);
        }
        i++;
    }
    return;
}

void set_socket(t_ping_env *env)
{
    int             sock_fd;
    int             yes;
    struct timeval	timeout;

	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
    yes = 1;
    sock_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock_fd < 0)
        print_error("Error: socket opening failed\n");
    env->ttl = 255;
    if (setsockopt(sock_fd, IPPROTO_IP, IP_HDRINCL, &yes, sizeof(yes)) < 0)
		print_error("Error: setsockopt failed\n");
    if (setsockopt(sock_fd, IPPROTO_IP, IP_TTL, &(env->ttl), sizeof(env->ttl)) == -1)
        print_error("Error: setsockopt failed\n");
    // if (setsockopt(sock_fd, IPPROTO_IP, IP_RECVTTL, &yes, sizeof(yes)) == -1)
        // print_error("Error: setsockopt failed\n");
    // if ((setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, (const void *)&timeout, sizeof(timeout))) == -1)
	// 	print_error("Error: setsockopt failed\n");
    env->sockfd = sock_fd;
}

void    configure_send(t_ping_env *env)
{  
    env->pkt.ip = (struct ip *)env->pkt.hdr_buf;
	env->pkt.hdr = (struct icmp *)(env->pkt.ip + 1);
    ft_bzero((void *)env->pkt.hdr_buf, PACKET_SIZE);
	env->pkt.ip->ip_v = 4;
	env->pkt.ip->ip_hl = sizeof(*(env->pkt.ip)) >> 2;
	env->pkt.ip->ip_ttl = env->ttl;
	env->pkt.ip->ip_p = IPPROTO_ICMP;
    inet_pton(AF_INET, env->host_dst, &(env->pkt.ip->ip_dst.s_addr));
    // env->daddr = env->pkt.ip->ip_dst.s_addr;
    // ft_memset(&(env->hdr_buf), 0, sizeof(env->hdr_buf));
    // env->hdr = (struct icmp *)env->hdr_buf;
    env->pkt.hdr->icmp_type = ICMP_ECHO; // icmp_type under mac and type under linux
    env->pkt.hdr->icmp_code = 0; // icmp_code under mac and code under linux
    env->pkt.hdr->icmp_cksum = calculate_checksum((unsigned short *)(env->pkt.hdr), sizeof(struct icmp)); // icmp_cksum under mac and checksum under linux
    env->pkt.hdr->icmp_hun.ih_idseq.icd_id = env->pid; // icmp_hun.ih_idseq.icd_id under mac and un.echo.id
    env->pkt.hdr->icmp_hun.ih_idseq.icd_seq = env->seq++; // icmp_hun.ih_idseq.icd_seq under mac and un.echo.sequence under linux
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
    env->interval = 1;

    env->min = 0.0;
    env->max = 0.0;
    env->cumul = 0;
    
    env->seq = 0;
    env->sent = 0;
    env->sent_pkt_count = 0;
    env->receive = 0;
    env->received_pkt_count = 0;
    env->timeout_flag = false;
    g_ping_loop = true;
    
    configure_send(env);
    printf("PING %s (%s) %d(%d) bytes of data.\n", env->hostname_dst, env->host_dst, 56, 84);
    // gettimeofday(&tv_start, NULL);
    // while(g_ping_loop == true)
    // {
        if ((env->sent = sendto(env->sockfd, &(env->pkt), PACKET_SIZE, 0, (struct sockaddr *)env->res->ai_addr, sizeof(struct sockaddr))) < 0)
        {
            // print_error("Error: sendto failed\n");
            exit(errno);
        }
        if (env->sent >= 0)
        {
            printf("caca\n");
            // env->sent_pkt_count++;
            // configure_receive(env);
            // env->receive = recvmsg(env->sockfd, &(env->ret_hdr), MSG_TRUNC);
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
        }
        // usleep(env->interval);
    // // }    
}

int main(int ac, char  **av) {
    t_ping_env env;
    t_options  opt;

    if (getuid() != 0)
		print_error("error: Operation not permitted\n");
    if (ac < 2)
        print_error("usage error: Destination address required\n");
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