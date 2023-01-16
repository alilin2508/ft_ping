/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:51:17 by alilin            #+#    #+#             */
/*   Updated: 2023/01/16 17:00:05 by alilin           ###   ########.fr       */
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
# include <time.h>
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

// typedef struct  ping_pkt
// {
//     struct icmp         *hdr; // !! struct icmphdr under linux and icmp under mac
//     // char                msg[sizeof(struct icmp)];
// }               t_ping_pkt;

typedef struct  ping_env
{
    int                 ttl; //send ttl settings: 255 on linux
    int                 timeout;
	double	            interval;
    
    int                 sockfd;
    
    struct icmp         *hdr; // !! struct icmphdr under linux and icmp under mac
    // struct t_ping_pkt   *send_hdr;
    pid_t               pid;
    int                 addr_len;
    
    int                 sent_pkt_count;
    int                 sent;
    bool                timeout_flag;
    bool                ping_loop;
    
    struct addrinfo     hints;
    struct addrinfo     *res;
    
    struct iovec        iov[1];
    struct msghdr       ret_hdr;
    int                 ret_ttl;    //returned ttl by the pinged system wich allows us to identify the operating system
    int                 received_pkt_count;
}               t_ping_env;

void            print_error(char *error);
char            *ft_getopt(char **av, char **options);
void            ft_handleopt(t_options *options, char *option);
void            configure_send(t_ping_env *env);
unsigned short  calculate_checksum(unsigned short *data, int len)

#endif