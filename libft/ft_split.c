/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 10:59:33 by alilin            #+#    #+#             */
/*   Updated: 2019/10/28 13:53:59 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		ft_countset(char const *s, char c)
{
	int		i;
	int		count;
	int		flag;

	i = 0;
	flag = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] != c && s[i])
		{
			flag = 1;
			i++;
		}
		if (flag == 1)
			count++;
		else
			i++;
		flag = 0;
	}
	return (count);
}

static char		*ft_mallocstr(char const *s, char c)
{
	int		i;
	int		size;
	char	*str;

	size = 0;
	while (s[size] && s[size] != c)
		size++;
	if (!(str = (char *)malloc(sizeof(char*) * (size + 1))))
		return (0);
	i = 0;
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char			**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (!(tab = (char **)malloc(sizeof(char *) * (ft_countset(s, c) + 1))))
		return (0);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != c && s[i])
		{
			tab[j] = ft_mallocstr(&s[i], c);
			while (s[i] != c && s[i])
				i++;
			j++;
		}
	}
	tab[j] = NULL;
	return (tab);
}
