/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 18:17:09 by alilin            #+#    #+#             */
/*   Updated: 2019/10/24 17:27:23 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lstnew;
	t_list	*start;

	start = NULL;
	while (lst)
	{
		if (!(lstnew = ft_lstnew((*f)(lst->content))))
		{
			ft_lstclear(&start, (*del));
			return (0);
		}
		ft_lstadd_back(&start, lstnew);
		lst = lst->next;
	}
	return (start);
}
