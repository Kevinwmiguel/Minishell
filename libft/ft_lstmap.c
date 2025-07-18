/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thguimar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:50:55 by thguimar          #+#    #+#             */
/*   Updated: 2023/10/23 19:07:27 by thguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*shelf;

	if (!f || !lst || !del)
		return (0);
	new_list = ft_lstnew(f(lst->content));
	if (!new_list-> content)
	{
		ft_lstclear(&new_list, del);
		return (0);
	}
	shelf = new_list;
	lst = lst->next;
	while (lst)
	{
		new_list->next = ft_lstnew(f(lst->content));
		if (!new_list->next)
		{
			ft_lstclear(&shelf, del);
			return (0);
		}
		new_list = new_list->next;
		lst = lst->next;
	}
	return (shelf);
}
