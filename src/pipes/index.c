/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 20:26:46 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/17 19:37:55 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	find_input_file_index(char **content, int i)
{
	while (content[i])
	{
		if (ft_strncmp(content[i], "<", 2) == 0)
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

int	find_double_right_index(t_cmd *cmd)
{
	int			i;
	t_cmd		*temp;

	temp = cmd;
	if (!temp->args)
		return (-1);
	i = 0;
	while (temp->args[i])
	{
		i++;
		if (ft_strncmp(temp->args[i], ">>", 2) == 0 && \
			ft_strlen(temp->args[i]) == 2)
			return (i);
	}
	return (-1);
}

int	is_redirection_token(char *s)
{
	return (!ft_strncmp(s, ">", 2) || !ft_strncmp(s, ">>", 3)
		|| !ft_strncmp(s, "<", 2) || !ft_strncmp(s, "<<", 3));
}