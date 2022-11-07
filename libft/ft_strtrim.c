/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 01:14:12 by thhusser          #+#    #+#             */
/*   Updated: 2020/11/04 01:14:12 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	charset(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*strnew(size_t size)
{
	char	*new;

	new = malloc(sizeof(char) * size + 1);
	if (!new)
		return (NULL);
	ft_bzero(new, size + 1);
	return (new);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	min;
	int	max;

	if (!s1)
		return (NULL);
	min = 0;
	while (s1[min] && charset(set, s1[min]) == 1)
		min++;
	max = ft_strlen(s1) - 1;
	while (min <= max && charset(set, s1[max]) == 1)
		max--;
	if (min == max)
		return (strnew(0));
	return (ft_substr(s1, min, (max - min + 1)));
}
