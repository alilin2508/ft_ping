/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 18:04:23 by thhusser          #+#    #+#             */
/*   Updated: 2021/07/29 18:04:23 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_next_line(int fd, char **line)
{
	int	ret;
	int	i;
	int	buf;

	ret = 1;
	i = 0;
	buf = 0;
	*line = malloc(400000);
	while (ret != 0 && buf != '\n')
	{
		ret = read(fd, &buf, 1);
		if (ret == 0 || buf == '\n')
			break ;
		(*line)[i++] = buf;
	}
	(*line)[i] = '\0';
	return (ret);
}
