/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 01:07:08 by thhusser          #+#    #+#             */
/*   Updated: 2021/09/24 01:07:08 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_list(t_list *list)
{
	char	*line;

	line = NULL;
	if (list)
	{
		while (list)
		{
			line = ft_strdup(list->content);
			ft_putstr(line);
			free(line);
			list = list->next;
		}
	}
}
