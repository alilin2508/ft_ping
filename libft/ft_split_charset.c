/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 02:01:40 by thhusser          #+#    #+#             */
/*   Updated: 2021/12/07 15:53:49 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_c(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	**count(char *str, char *charset, char **tab)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && is_c(str[i], charset) == 0)
			i++;
		words++;
		while (str[i] && is_c(str[i], charset) == 1)
			i++;
	}
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	tab[words] = 0;
	return (tab);
}

static char	**letters(char *str, char *charset, char **tab)
{
	int	i;
	int	index;
	int	letters;

	i = 0;
	index = 0;
	while (str[i])
	{
		letters = 0;
		while (str[i] && is_c(str[i], charset) == 0)
		{
			letters++;
			i++;
		}
		tab[index] = malloc(sizeof(char) * letters + 1);
		if (!tab[index])
			return (NULL);
		tab[index][letters] = '\0';
		index++;
		while (str[i] && is_c(str[i], charset) == 1)
			i++;
	}
	return (tab);
}

static char	**copycopy(char *str, char *charset, char **tab)
{
	int	i;
	int	index;
	int	letters;

	i = 0;
	index = 0;
	while (str[i])
	{
		letters = 0;
		while (str[i] && is_c(str[i], charset) == 0)
		{
			tab[index][letters] = str[i];
			letters++;
			i++;
		}
		index++;
		while (str[i] && is_c(str[i], charset) == 1)
			i++;
	}
	return (tab);
}

char	**ft_split_charset(char *str, char *charset)
{
	char	**tab;

	tab = NULL;
	while (*str && is_c(*str, charset) == 1)
		str++;
	tab = count(str, charset, tab);
	tab = letters(str, charset, tab);
	tab = copycopy(str, charset, tab);
	return (tab);
}
