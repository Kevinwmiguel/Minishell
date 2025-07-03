/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 20:13:23 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/03 16:03:33 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	is_redirection_token(char *s)
{
	return (!ft_strncmp(s, ">", 2) || !ft_strncmp(s, ">>", 3)
		|| !ft_strncmp(s, "<", 2) || !ft_strncmp(s, "<<", 3));
}

void	remove_all_output_redirs(t_cmd *cmd, int *last_index, char **last_type)
{
	int	i;

	i = 0;
	*last_index = -1;
	*last_type = NULL;
	while (cmd->args[i])
	{
		if ((ft_strncmp(cmd->args[i], ">", 2) == 0 || \
		ft_strncmp(cmd->args[i], ">>", 3) == 0)
			&& cmd->args[i + 1])
		{
			create_empty_output_file(cmd->args[i], cmd->args[i + 2]);
			*last_index = i;
			*last_type = cmd->args[i];
		}
		i++;
	}
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

void	handle_redirection_right_input(t_cmd *cmd)
{
	int		last_index;
	char	*redir_type;

	if (!cmd || !cmd->args)
		return ;
	find_last_output_redir(cmd, &last_index, &redir_type);
	if (last_index == -1)
		return ;
	open_last_output_file(cmd, last_index, redir_type);
}
