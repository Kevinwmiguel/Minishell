/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outputs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:59:30 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/16 22:54:41 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	open_last_output_file(t_cmd *cmd, int last_index, \
	char *redir_type, t_shell *shell)
{
	if (ft_strncmp(redir_type, ">>", 3) == 0)
	{
		cmd->redirect->outfd = open(cmd->args[last_index + 1], \
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else if (ft_strncmp(redir_type, ">", 2) == 0)
	{
		cmd->redirect->outfd = open(cmd->args[last_index + 1], \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (cmd->redirect->outfd < 0)
	{
		perror("open");
		shell->exit_code = 126;
	}
}

void	find_last_output_redir(t_cmd *cmd, int *last_index, char **redir_type)
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
