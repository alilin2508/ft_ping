/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 01:12:23 by thhusser          #+#    #+#             */
/*   Updated: 2020/11/04 01:12:23 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void			*temp;
	unsigned char	*temp_ptr;
	size_t			i;

	i = 0;
	temp = malloc(size);
	if (!temp)
		return (NULL);
	temp_ptr = (unsigned char *)temp;
	while (i < size)
		temp_ptr[i++] = 0;
	return (temp);
}
