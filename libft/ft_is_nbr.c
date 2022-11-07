/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 23:56:29 by thhusser          #+#    #+#             */
/*   Updated: 2021/09/23 23:56:29 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_nbr(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
			i++;
		else
		{
			while (str[i])
			{
				if (str[i] >= '0' && str[i] <= '9')
					i++;
				else
					return (0);
			}
		}
	}
	return (1);
}
