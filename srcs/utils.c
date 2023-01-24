/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:58:30 by alilin            #+#    #+#             */
/*   Updated: 2023/01/24 17:18:57 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	print_error(char *error)
{
	fprintf(stderr, "ping: %s", error);
	exit(errno);
}

unsigned short	checksum(unsigned short *data, int len)
{
	unsigned long	checksum;

	checksum = 0;
	while (len > 1)
	{
		checksum = checksum + *data++;
		len = len - sizeof(unsigned short);
	}
	if (len)
		checksum = checksum + *(unsigned char*)data;
	checksum = (checksum >> 16) + (checksum & 0xffff);
	checksum = checksum + (checksum >> 16);
	return (unsigned short)(~checksum);
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
		{
			free(env->rttbuf);
			print_error("Error: malloc failed\n");
		}
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