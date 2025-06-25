/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_cleaner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:02:27 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/26 00:09:34 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

char    *special_cleaner(const char *s1, const char *s2, t_shell *shell)
{
	char		*tmp;

	tmp = NULL;
	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	shell->list->listc = tmp;
	shell->list = shell->list->next;
	return (tmp);
}
