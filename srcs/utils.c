/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:58:30 by alilin            #+#    #+#             */
/*   Updated: 2023/01/23 19:08:22 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	print_error(char *error) {
	free_all();
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

void free_all()
{
	if (env != NULL)
		free(env);
}
