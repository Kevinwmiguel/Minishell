/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:56:16 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/18 18:56:44 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	join_expand(t_shell *data, char **result, char **str,
		bool is_double_quote)
{
	char	*tmp[2];

	tmp[0] = expand_result(data, str, is_double_quote);
	tmp[1] = ft_strjoin(*result, tmp[0]);
	if (*result)
		free(*result);
	if (tmp[0])
		free(tmp[0]);
	*result = tmp[1];
}
