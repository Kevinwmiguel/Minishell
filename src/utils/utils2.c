/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:59:42 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/24 12:59:41 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	root_signal(int signal, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	is_illegal_file_read(t_cmd *cmd, t_pipexinfo *info)
{
	int	i;

	if (!cmd || !cmd->args || info->fd_in == 0)
		return (0);
	if (ft_strncmp(cmd->args[0], "cat", 4) != 0)
		return (0);
	i = 1;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] != '<' && cmd->args[i][0] != '-')
			return (1);
		i++;
	}
	return (0);
}

void	free_cmds(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->args)
			free_split(cmd->args);
		if (cmd->redirect)
			free_redirections(cmd->redirect);
		free(cmd);
		cmd = tmp;
	}
}

int	is_heredoc(t_cmd *cmd)
{
	t_red	*redir;

	redir = cmd->redirect;
	while (redir)
	{
		if (redir->type == HEREDOC)
			return (1);
		redir = redir->next;
	}
	return (0);
}

void	file_checker(t_shell *sh, char *full)
{
	if (access(full, F_OK) != 0)
	{
		ft_putstr_fd(full, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(full);
		final_cleaner(sh);
		exit(127);
	}
	if (check_is_dir(full))
	{
		ft_putstr_fd(full, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		free(full);
		final_cleaner(sh);
		exit(126);
	}
	if (access(full, X_OK) != 0)
	{
		ft_putstr_fd(full, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		free(full);
		final_cleaner(sh);
		exit(126);
	}
}
