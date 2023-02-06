/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:13:20 by alilin            #+#    #+#             */
/*   Updated: 2023/02/06 18:27:31 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	print_ttl(t_ping_env *env)
{
	char	str[INET_ADDRSTRLEN];
	
	printf("From _gateway (%s) icmp_seq=%d Time to live exceeded\n", inet_ntop(AF_INET, (void*)&env->pkt.ip->saddr, str, INET_ADDRSTRLEN), env->sent_pkt_count);
	env->error_pkt_count++;
}

void	print_verbose(t_ping_env *env)
{
	char	str[INET_ADDRSTRLEN];

	printf("From _gateway (%s) icmp_seq=%d type=%d code=%d\n", inet_ntop(AF_INET, (void*)&env->pkt.ip->saddr, str, INET_ADDRSTRLEN), env->sent_pkt_count, env->pkt.hdr->type, env->pkt.hdr->code);
	env->error_pkt_count++;
}

void	disp_stats(t_ping_env *env)
{
	long double	avg;
	long double loss;
	long double	mdev;

	mdev = 0.0;
    loss = (((env->sent_pkt_count - env->received_pkt_count) / env->sent_pkt_count) * 100);
	avg = env->avg / env->received_pkt_count;
	if (env->received_pkt_count != 0)
	{
		for (int i = 0; env->rttbuf[i] != -1; i++)
		{
			mdev += fabsl(env->rttbuf[i] - env->avg);
		}
		mdev /= env->received_pkt_count;
	}
	printf("%d/%d packets, %.0Lf%% loss, min/avg/mdev/max = %.3Lf/%.3Lf/%.3Lf/%.3Lf ms\n", env->received_pkt_count, env->sent_pkt_count, loss, env->min, env->avg, mdev, env->max);
}

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
	if (env->received_pkt_count != 0)
	{
		for (int i = 0; env->rttbuf[i] != -1; i++)
		{
			mdev += fabsl(env->rttbuf[i] - env->avg);
		}
		mdev /= env->received_pkt_count;
		free(env->rttbuf);
	}
    printf("\n--- %s ping statistics ---\n", env->hostname_dst);
    if (env->error_pkt_count != 0)
	{
        printf("%d packets transmitted, %d received, +%d errors, %.0Lf%% packet loss, time %.0Lfms\n", env->sent_pkt_count, env->received_pkt_count, env->error_pkt_count, loss, time);
		if (env->received_pkt_count != 0)
			printf("rtt min/avg/max/mdev = %.3Lf/%.3Lf/%.3Lf/%.3Lf ms\n", env->min, env->avg, env->max, mdev);
	}
    else if (env->received_pkt_count > 0 && env->error_pkt_count == 0)
	{
        printf("%d packets transmitted, %d received, %.0Lf%% packet loss, time %.0Lfms\n", env->sent_pkt_count, env->received_pkt_count, loss, time);
    	printf("rtt min/avg/max/mdev = %.3Lf/%.3Lf/%.3Lf/%.3Lf ms\n", env->min, env->avg, env->max, mdev);
	}
	else
	{
		printf("%d packets transmitted, %d received, %.0Lf%% packet loss, time %.0Lfms\n", env->sent_pkt_count, env->received_pkt_count, loss, time);
	}
}
