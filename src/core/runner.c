/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 00:41:04 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/23 11:02:03 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

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

int	ft_find_last(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	count--;
	while (count >= 0)
	{
		if (ft_strncmp(args[count], "<<", 3) == 0)
			return (0);
		if (ft_strncmp(args[count], "<", 2) == 0)
			return (1);
		count--;
	}
	return (-1);
}

void	redirect_io(t_red *redir, t_pipexinfo *info, int last_cmd)
{
	(void)info;
	if (last_cmd == 0 && redir && redir->heredoc > 0)
	{
		dup2(redir->heredoc, STDIN_FILENO);
		close(redir->heredoc);
	}
	else if (last_cmd == 1 && redir && redir->infd > 0)
	{
		dup2(redir->infd, STDIN_FILENO);
		close(redir->infd);
	}
	else if (redir && redir->heredoc > 0)
	{
		dup2(redir->heredoc, STDIN_FILENO);
		close(redir->heredoc);
	}
	else if (redir && redir->infd > 0)
	{
		dup2(redir->infd, STDIN_FILENO);
		close(redir->infd);
	}
	else if (info->fd_in > 0 && info->fd_in != STDIN_FILENO)
		dup2(info->fd_in, STDIN_FILENO);
}

void	run_children(t_shell *shell, t_cmd_r *clean \
	, t_pipexinfo *info, t_cmd *cmd)
{
	t_red	*redir;
	int		last_cmd;

	redir = cmd->redirect;
	if (is_illegal_file_read(cmd, info))
	{
		close_extra_fds();
		freedom(shell);
		exit(1);
	}
	last_cmd = ft_find_last(cmd->args);
	redirect_io(redir, info, last_cmd);
	if (redir && redir->outfd > 0)
		dup2(redir->outfd, STDOUT_FILENO);
	else if (info->fd[1] > 0)
		dup2(info->fd[1], STDOUT_FILENO);
	if (info->fd[0] > 0)
		close(info->fd[0]);
	if (info->fd[1] > 0)
		close(info->fd[1]);
	if (info->fd_in > 0 && info->fd_in != STDIN_FILENO)
		close(info->fd_in);
	executor(shell, clean);
}

void	store_exit_and_args(t_shell *shell, t_cmd_r *clean, int status)
{
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
	else
		shell->exit_code = 1;
	save_last_cmd(shell, clean->args);
	if (shell->last_arg)
		free(shell->last_arg);
	if (shell->next_last_arg)
		shell->last_arg = ft_strdup(shell->next_last_arg);
	else
		shell->last_arg = NULL;
}

void	run_child(t_cmd_r *clean, t_shell *shell, t_pipexinfo *info)
{
	int	processor;
	int	status;

	processor = fork();
	if (processor == 0)
	{
		if (is_heredoc(shell->cmd))
			signal_search(HEREDOC_CHILD);
		else
			signal_search(CHILD);
		run_children(shell, clean, info, shell->cmd);
	}
	else if (processor > 0)
	{
		waitpid(processor, &status, 0);
		store_exit_and_args(shell, clean, status);
	}
	else
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}
