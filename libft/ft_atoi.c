/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 17:30:16 by thhusser          #+#    #+#             */
/*   Updated: 2021/11/30 17:10:35 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(const char str)
{
	if (str == ' ' || str == '\t' || str == '\n'
		|| str == '\v' || str == '\f' || str == '\r')
		return (1);
	return (0);
}

static int	ft_number(const char str)
{
	if (str >= '0' && str <= '9')
		return (1);
	return (0);
}

static int	ft_sign(const char *str)
{
	int	sign;
	int	nb;

	sign = 0;
	nb = 0;
	while (str[nb] == '-' || str[nb] == '+')
	{
		if (str[nb] == '-')
			sign++;
		nb++;
	}
	if (nb > 1)
		return (-1);
	return (sign);
}

int	ft_atoi(const char *str)
{
	int			i;
	long int	result;
	int			sign;

	i = 0;
	result = 0;
	sign = 0;
	while (ft_isspace(*str))
		str++;
	sign = ft_sign(str);
	if (sign == -1)
		return (0);
	while (*str == '-' || *str == '+')
		str++;
	result = 0;
	while (ft_number(str[i]))
		result = (str[i++] - 48) + result * 10;
	if ((sign % 2))
		result = -result;
	return (result);
}
