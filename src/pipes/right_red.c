/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 20:13:23 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/29 21:49:41 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	remove_all_output_redirs(t_cmd *cmd, int last_index)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		if ((i != last_index) && \
			(ft_strncmp(cmd->args[i], ">", 2) == 0 || \
			ft_strncmp(cmd->args[i], ">>", 3) == 0) && \
				cmd->args[i + 1])
		{
			create_empty_output_file(cmd->args[i], cmd->args[i + 1]);
			remove_redir_pair(cmd, i);
			continue ;
		}
		i++;
	}
	remove_last_redir_pair(cmd, last_index);
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
	remove_all_output_redirs(cmd, last_index);
}

void	open_last_output_file(t_cmd *cmd, \
	int last_index, char *redir_type)
{
	if (ft_strncmp(redir_type, ">>", 2) == 0)
	{
		cmd->redirect->outfd = open(cmd->args[last_index + 1], \
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		cmd->redirect->outfd = open(cmd->args[last_index + 1], \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (cmd->redirect->outfd < 0)
	{
		perror("open");
		exit(1);
	}
}

void	find_last_output_redir(t_cmd *cmd, \
	int *last_index, char **redir_type)
{
	int	i;

	i = 0;
	*last_index = -1;
	*redir_type = NULL;
	while (cmd->args[i])
	{
		if ((ft_strncmp(cmd->args[i], ">", 2) == 0 || \
			ft_strncmp(cmd->args[i], ">>", 3) == 0) && \
			cmd->args[i + 1])
		{
			*last_index = i;
			*redir_type = cmd->args[i];
		}
		i++;
	}
}
