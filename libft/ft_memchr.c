/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 01:12:29 by thhusser          #+#    #+#             */
/*   Updated: 2020/11/04 01:12:29 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_ptr;
	size_t			i;

	i = 0;
	s_ptr = (unsigned char *)s;
	while (i < n)
	{
		if (s_ptr[i] == (unsigned char)c)
			return (s_ptr + i);
		i++;
	}
	return (NULL);
}
