/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:28:02 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/26 16:47:57 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	executor(t_shell *shell, char **argv)
{
	int		flag;
	char	*fullpath;

	if (!argv || !argv[0])
		exit(1);
	flag = builtins(shell->cmd->args[0]);
	if (flag > 0)
	{
		builtins_analyzer(shell, flag);
		exit(1);
	}
	else
	{
		fullpath = get_path(shell->cmd->args[0], shell->env);
		execve(fullpath, argv, shell->env);
		perror("execve: ");
		exit(1);
	}
}

void	line_helper(t_pipexinfo *info)
{
	info->fd[0] = -1;
	info->fd[1] = -1;
}

void	line_helper2(t_pipexinfo *info)
{
	if (info->fd[1] != -1)
		close(info->fd[1]);
	if (info->fd_in != STDIN_FILENO)
		close(info->fd_in);
}

static void	fork_loop(t_shell *shell, t_pipexinfo *info)
{
	t_cmd	*cmd;

	cmd = shell->cmd;
	while (cmd)
	{
		shell->cmd = cmd;
		if (cmd->next && pipe(info->fd) == -1)
			exit(1);
		if (!cmd->next)
			line_helper(info);
		info->pid = fork();
		if (info->pid == 0)
		{
			if (info->fd[1] != -1)
				close(info->fd[0]);
			run_children(shell, cmd->args, info);
		}
		line_helper2(info);
		info->fd_in = info->fd[0];
		cmd = cmd->next;
	}
	while (wait(NULL) != -1)
		;
}

void	execute_all_cmds(t_shell *shell)
{
	t_pipexinfo	info;
	t_cmd		*cmd;

	ft_bzero(&info, sizeof(t_pipexinfo));
	info.fd_in = STDIN_FILENO;
	shell->count = 0;
	cmd = shell->cmd;
	while (cmd)
	{
		shell->count++;
		if (cmd->redirect)
			fixing_cmd_red(cmd);
		cmd = cmd->next;
	}
	if (shell->count == 1)
		return (builtins_dealer(shell, &info));
	fork_loop(shell, &info);
}
