/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 01:13:10 by thhusser          #+#    #+#             */
/*   Updated: 2020/11/04 01:13:10 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(char **tab, int index)
{
	while (index >= 0)
	{
		free((void *)tab[index]);
		index--;
	}
	free(tab);
	return (NULL);
}

static char	**count_words(char const *str, char charset, char **tab)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] && str[i] != charset)
			i++;
		words++;
		while (str[i] && str[i] == charset)
			i++;
	}
	tab = (char **)malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	tab[words] = 0;
	return (tab);
}

static char	**count_letters(char const *str, char charset, char **tab)
{
	int	i;
	int	index;
	int	letters;

	i = 0;
	index = 0;
	while (str[i])
	{
		letters = 0;
		while (str[i] && str[i] != charset)
		{
			letters++;
			i++;
		}
		tab[index] = malloc(sizeof(char) * letters + 1);
		if (!tab[index])
			return (ft_free(tab, index));
		tab[index][letters] = 0;
		index++;
		while (str[i] && str[i] == charset)
			i++;
	}
	return (tab);
}

static char	**split_copy(char const *str, char charset, char **tab)
{
	int	i;
	int	index;
	int	letters;

	i = 0;
	index = 0;
	while (str[i])
	{
		letters = 0;
		while (str[i] && str[i] != charset)
			tab[index][letters++] = str[i++];
		index++;
		while (str[i] && str[i] == charset)
			i++;
	}
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s || !c)
		return (NULL);
	while (*s && *s == c)
		s++;
	tab = NULL;
	tab = count_words(s, c, tab);
	tab = count_letters(s, c, tab);
	tab = split_copy(s, c, tab);
	return (tab);
}
