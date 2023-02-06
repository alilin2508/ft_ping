/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:51:17 by alilin            #+#    #+#             */
/*   Updated: 2023/02/06 18:28:19 by alilin           ###   ########.fr       */
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
# include <arpa/inet.h>
# include <netdb.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <errno.h>
# include <math.h>

#define PACKET_SIZE 64

typedef struct	options
{
	bool			h;
	bool			v;
	bool			error;
}		t_options;

typedef struct	pkt
{
	char			hdr_buf[PACKET_SIZE];
	struct iphdr		*ip; // !! struct iphdr under linux and ip under mac
	struct icmphdr		*hdr; // !! struct icmphdr under linux and icmp under mac
}				t_pkt;

typedef struct	s_res
{
	struct iovec		iov[1];
	struct msghdr		ret_hdr;
}		t_res;

typedef struct	ping_env
{	
	int				ttl; // 255 on linux
	double			interval;

	int			sockfd;

	t_pkt			pkt;
	pid_t			pid;
	int			seq;
    
	char			host_dst[INET_ADDRSTRLEN];
	char			*hostname_dst;
	int			sent_pkt_count;

	struct timeval		start;
	struct timeval		end;
	struct timeval		s;
	struct timeval		r;

	long double			rtt;
	long double			min;
	long double			max;
	long double			avg;
	long double			*rttbuf;
    
	struct addrinfo		hints;
	struct addrinfo		*res;
	struct sockaddr_in	*sa_in;
    
	t_res			response;
	int			bytes;
	int			received_pkt_count;
	int			error_pkt_count;
}               t_ping_env;

static bool		g_send[1];

void		print_error(char *error);
char		*ft_getopt(char **av, char **options);
void		ft_handleopt(t_options *options, char *option);
unsigned short 	checksum(unsigned short *data, int len);
void    	configure_send(t_ping_env *env);
void    	configure_receive(t_ping_env *env);
void		send_packet(t_ping_env *env);
void		get_packet(t_ping_env *env);
void    	calc_rtt(t_ping_env *env);
void		disp_stats(t_ping_env *env);
void    	get_statistic(t_ping_env *env);
void		print_verbose(t_ping_env *env);
void		print_ttl(t_ping_env *env);

#endif
