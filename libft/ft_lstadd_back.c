/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 01:12:03 by thhusser          #+#    #+#             */
/*   Updated: 2020/11/04 01:12:03 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*list;

	if (alst == NULL || *alst == NULL)
	{
		*alst = new;
	}
	else
	{
		list = *alst;
		while (list->next != NULL)
			list = list->next;
		list->next = new;
	}
}
