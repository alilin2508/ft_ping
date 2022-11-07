/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 01:13:50 by thhusser          #+#    #+#             */
/*   Updated: 2020/11/04 01:13:50 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*dest;

	i = 0;
	if (!s)
		return (NULL);
	dest = malloc(sizeof(char) * (ft_strlen((char *)s) + 1));
	if (!dest)
		return (NULL);
	while (s[i])
	{
		dest[i] = (*f)((char)s[i]);
		i++;
	}
	dest[i] = 0;
	return (dest);
}
