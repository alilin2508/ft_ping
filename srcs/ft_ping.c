/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:54:59 by alilin            #+#    #+#             */
/*   Updated: 2023/01/16 17:01:51 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void int_handler(t_ping_env *env) {
    env->ping_loop = false;
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
            env->hints.ai_socktype = SOCK_DGRAM;
            env->hints.ai_protocol = IPPROTO_ICMP;
            ret = getaddrinfo(NULL, av[i], &(env->hints), &(env->res));
            if (ret != 0)
            {
                fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
                exit(EXIT_FAILURE);
            }
            break;
        }
        i++;
    }
    return;
}

void set_socket(t_ping_env *env)
{
    int yes;

    yes = 1;
    env->sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_ICMP);
    if (env->sockfd < 0)
    {
        fprintf(stderr, "Error: socket opening failed\n");
        exit(EXIT_FAILURE);
    }
    env->ttl = 255;
    if (setsockopt(env->sockfd, SOL_SOCKET, IP_TTL, &(env->ttl), sizeof(env->ttl)) == -1)
    {
        fprintf(stderr, "Error: setsockopt failed\n");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(env->sockfd, SOL_SOCKET, IP_RECVTTL, &yes, sizeof(yes)) == -1)
    {
        fprintf(stderr, "Error: setsockopt failed\n");
        exit(EXIT_FAILURE);
    }
}

void ping_loop(t_ping_env *env)
{
    struct timeval	tv_start, tv_end;
    
    env->timeout = 1;
    env->interval = 0.5;
    
    env->pid = getpid();
    
    env->sent_pkt_count = 0;
    env->received_pkt_count = 0;
    env->sent = 0;
    env->timeout_flag = false;
    env->ping_loop = true;
    
    // display first line info !!!! TO DO
    while(env->ping_loop)
    {
        configure_send(env);
        gettimeofday(&tv_start, NULL);
        if ((env->sent = sendto(env->sockfd, &(env->hdr), sizeof(env->hdr), 0, env->res->ai_addr, env->res->ai_addrlen)) < 0)
            printf("caca");  
    }    
}

int main(int ac, char  **av) {
    t_ping_env env;
    t_options   opt;

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
    ping_loop(&env);
    signal(SIGINT, int_handler);
    return (0);
}