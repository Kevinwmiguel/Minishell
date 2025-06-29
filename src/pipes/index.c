/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 20:26:46 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/29 21:49:04 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	find_input_file_index(char **content, int i)
{
	while (content[i])
	{
		if (ft_strncmp(content[i], "<", 1) == 0)
		{
			if (content[i + 1])
				return (i + 1);
			else
				return (-1);
		}
		i++;
	}
	return (-1);
}

int	find_next_double_left_index(t_cmd *cmd, int start)
{
	int	i;

	i = start;
	while (cmd->args[i])
	{
		if (ft_strncmp(cmd->args[i], "<<", 3) == 0 && \
			ft_strlen(cmd->args[i]) == 2)
			return (i);
		i++;
	}
	return (-1);
}
