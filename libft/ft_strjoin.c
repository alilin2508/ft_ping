/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 01:13:41 by thhusser          #+#    #+#             */
/*   Updated: 2020/11/04 01:13:41 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*strcat(char *dest, char const *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
		dest[i++] = src[j++];
	dest[i] = 0;
	return (dest);
}

static char	*strcpy(char *dest, char const *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*str;
	size_t		size;

	if (!s1 || !s2)
		return (NULL);
	if (s1 && s2)
		size = ft_strlen(s1) + ft_strlen(s2) + 1;
	else if (s1)
		size = ft_strlen(s1);
	else if (s2)
		size = ft_strlen(s2);
	else
		return (NULL);
	str = (char *)malloc(sizeof(char) * size);
	if (!str)
		return (NULL);
	str = strcpy(str, s1);
	str = strcat(str, s2);
	return (str);
}
