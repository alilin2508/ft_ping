/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:54:59 by alilin            #+#    #+#             */
/*   Updated: 2023/01/11 19:28:32 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void intHandler(t_ping_env *env) {
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
    if (setsockopt(env->sockfd, SOL_SOCKET, IP_TTL, &(env->ttl), sizeof(env->ttl)) == -1);
    {
        fprintf(stderr, "Error: setsockopt failed\n");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(env->sockfd, SOL_SOCKET, IP_RECVTTL, &yes, sizeof(yes)) == -1);
    {
        fprintf(stderr, "Error: setsockopt failed\n");
        exit(EXIT_FAILURE);
    }
}

int main(int ac, char  **av) {
    t_ping_env env;
    
    if (ac < 2) {
        print_error("usage error: Destination address required\n");
    }
    t_options   opt;
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
    signal(SIGINT, int_handler(&env));
    return (0);
}