/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:25:10 by alilin            #+#    #+#             */
/*   Updated: 2019/10/28 11:35:41 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_size(long nb)
{
	int		size;

	size = 1;
	if (nb < 0)
	{
		nb = -nb;
		size += 1;
	}
	while (nb >= 10)
	{
		size++;
		nb = nb / 10;
	}
	return (size);
}

char			*ft_itoa(int n)
{
	char			*str;
	int				i;
	int				size;
	unsigned int	nb;

	size = ft_size(n);
	if (!(str = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	if (n < 0)
		nb = -n;
	else
		nb = n;
	i = size - 1;
	while (nb >= 10)
	{
		str[i] = nb % 10 + 48;
		nb /= 10;
		i--;
	}
	if (n < 0)
		str[0] = '-';
	str[i] = nb % 10 + 48;
	str[size] = '\0';
	return (str);
}
