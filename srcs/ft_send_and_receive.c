/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_send_and_receive.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:13:14 by alilin            #+#    #+#             */
/*   Updated: 2023/01/16 16:15:18 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void    configure_send(t_ping_env *env)
{
    int i;
    
    env->sent = 0;
    ft_bzero(&(env->hdr), sizeof(env->hdr));
    env->hdr->icmp_type = ICMP_ECHO; // icmp_type under mac and typeunder linux
    env->hdr->icmp_code = 0; // icmp_code under mac and code under linux
    env->hdr->icmp_cksum = calculate_checksum(&(env->hdr), sizeof(env->hdr)); // icmp_cksum under mac and checksum under linux
    env->hdr->icmp_hun.ih_idseq.icd_id = env->pid; // icmp_hun.ih_idseq.icd_id under mac and un.echo.id
    env->hdr->icmp_hun.ih_idseq.icd_seq = env->sent_pkt_count++; // icmp_hun.ih_idseq.icd_seq under mac and un.echo.sequence under linux
}