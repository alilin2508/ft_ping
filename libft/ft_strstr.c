/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 01:14:09 by thhusser          #+#    #+#             */
/*   Updated: 2020/11/04 01:14:09 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (to_find[0] == 0)
		return (str);
	while (str[i])
	{
		j = 0;
		if (to_find[j] == str[i])
		{
			while (to_find[j] && to_find[j] == str[i + j])
				j++;
			if (to_find[j] == 0)
				return (str + i);
		}
		i++;
	}
	return (NULL);
}
