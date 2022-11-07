/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 01:14:06 by thhusser          #+#    #+#             */
/*   Updated: 2020/11/04 01:14:06 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	car;

	i = 0;
	car = (unsigned char)c;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == car)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}
