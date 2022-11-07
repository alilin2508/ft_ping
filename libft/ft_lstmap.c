/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 01:12:17 by thhusser          #+#    #+#             */
/*   Updated: 2020/11/04 01:12:17 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*ptr;

	newlst = NULL;
	while (lst)
	{
		ptr = ft_lstnew((*f)(lst->content));
		if (!ptr)
		{
			ft_lstclear(&newlst, (*del));
			return (0);
		}
		ft_lstadd_back(&newlst, ptr);
		lst = lst->next;
	}
	return (newlst);
}
