/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:51:17 by alilin            #+#    #+#             */
/*   Updated: 2023/01/19 16:19:07 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include "libft.h"
# include <sys/socket.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <fcntl.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <netinet/ip_icmp.h>

typedef struct  options
{
    bool                h;
    bool                v;
    bool                error;
}               t_options;

typedef struct  ping_env
{
    int                 ttl; //send ttl settings: 255 on linux
    int                 timeout;
	double	            interval;
    
    int                 sockfd;
    
    struct icmphdr      *hdr; // !! struct icmphdr under linux and icmp under mac
    pid_t               pid;

    char                buf[76];
    char                retbuf[1000];
    
    char                *host_dst;
    char				*hostname_dst;
    int                 sent_pkt_count;
    int                 sent;
    bool                timeout_flag;

    double              min;
    double              max;
    double			    cumul;
    
    struct addrinfo     hints;
    struct addrinfo     *res;
    
    int                 receive;
    struct iovec        iov[1];
    struct msghdr       ret_hdr;
    int                 ret_ttl;    //returned ttl by the pinged system wich allows us to identify the operating system
    int                 received_pkt_count;
}               t_ping_env;
    
static bool             g_ping_loop;

void            print_error(char *error);
char            *ft_getopt(char **av, char **options);
void            ft_handleopt(t_options *options, char *option);
unsigned short  calculate_checksum(unsigned short *data, int len);

#endif