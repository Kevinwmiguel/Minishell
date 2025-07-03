/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:36:09 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/03 09:51:17 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void fixing_cmd_red(t_cmd *cmd, t_cmd_r *clean)
{
	handle_redirection_left_input(cmd);
	handle_redirection_right_input(cmd);
	import_args_to_clean(cmd, clean);
}

void	remove_last_redir_pair(t_cmd *cmd, int index)
{
	int	j;

	j = index;
	while (cmd->args[j + 2])
	{
		cmd->args[j] = cmd->args[j + 2];
		j++;
	}
	cmd->args[j] = NULL;
	cmd->args[j + 1] = NULL;
}

void	remove_redir_pair(t_cmd *cmd, int i)
{
	int	j;

	free(cmd->args[i]);
	free(cmd->args[i + 1]);
	j = i;
	while (cmd->args[j + 2])
	{
		cmd->args[j] = cmd->args[j + 2];
		j++;
	}
	cmd->args[j] = NULL;
	cmd->args[j + 1] = NULL;
}

int	create_empty_output_file(char *type, char *filename)
{
	int	fd;

	if (ft_strncmp(type, ">>", 2) == 0)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	return (fd);
}
