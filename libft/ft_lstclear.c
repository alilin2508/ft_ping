/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 17:02:19 by alilin            #+#    #+#             */
/*   Updated: 2019/10/23 13:59:16 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (lst)
		while (*lst)
		{
			tmp = *lst;
			ft_lstdelone(tmp, del);
			*lst = tmp;
			*lst = (*lst)->next;
		}
	*lst = NULL;
}
