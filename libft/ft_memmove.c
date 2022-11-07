/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:47:38 by alilin            #+#    #+#             */
/*   Updated: 2019/10/24 13:57:35 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*cdst;
	char	tmp[len];

	cdst = dst;
	if (!dst && !src)
		return (NULL);
	ft_memcpy(tmp, src, len);
	ft_memcpy(cdst, tmp, len);
	return (cdst);
}
