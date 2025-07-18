/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thguimar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:05:20 by thguimar          #+#    #+#             */
/*   Updated: 2023/10/23 12:37:46 by thguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lista;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			lista = ft_lstlast(*(lst));
			lista->next = new;
		}
	}
}
