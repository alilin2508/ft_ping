/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 01:10:41 by thhusser          #+#    #+#             */
/*   Updated: 2020/11/04 01:10:41 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*dest_ptr;
	unsigned char	*src_ptr;
	size_t			i;

	i = 0;
	dest_ptr = (unsigned char *)dest;
	src_ptr = (unsigned char *)src;
	while (i < n)
	{
		*dest_ptr = *src_ptr;
		if (*src_ptr == (unsigned char)c)
			return (dest + i + 1);
		dest_ptr++;
		src_ptr++;
		i++;
	}
	return (NULL);
}
