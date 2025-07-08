/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:28:02 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/06 20:48:35 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	executor(t_shell *shell, t_cmd_r *clean)
{
	int		flag;
	char	*fullpath;

	if (!clean->args || !clean->args[0])
		exit(1);
	flag = builtins(clean->args[0]);
	if (flag > 0)
	{
		if (!ft_strncmp(clean->args[0], "export", 7) && shell->count > 1 && !clean->args[1])
			export_print(shell->exp);
		else
			builtins_analyzer(shell, flag, clean->args);
		free_token_list(shell);
		close_redirections(shell->cmd);
		final_cleaner(shell);
		exit(1);
	}
	else
	{
		fullpath = get_path(clean->args[0], shell->env);
		if (!fullpath)
		{
			perror("command not found");
			final_cleaner(shell);
			exit(127);
		}
		execve(fullpath, clean->args, shell->env);
		perror("execve: ");
		free(fullpath);
		final_cleaner(shell);
		exit(127);
	}
}

static void	fork_loop(t_shell *shell, t_pipexinfo *info, t_cmd_r *clean)
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
			run_children(shell, clean, info);
		}
		line_helper2(info);
		info->fd_in = info->fd[0];
		clean = clean->next;
		cmd = cmd->next;
	}
	while (wait(NULL) != -1)
		;
}

void	execute_or_fork(t_shell *shell, t_pipexinfo *info)
{
	t_cmd_r	*clean;

	clean = shell->cmd_ready;
	if (shell->count == 1)
	{
		builtins_dealer(shell, info, clean);
		free_cmdr(clean);
		shell->cmd_ready = NULL;
		return ;
	}
	fork_loop(shell, info, clean);
	free_cmdr(clean);
	shell->cmd_ready = NULL;
}

void	count_and_fix_cmds(t_shell *shell)
{
	t_cmd	*cmd;
	t_cmd_r	*clean;

	cmd = shell->cmd;
	clean = shell->cmd_ready;
	shell->count = 0;
	while (cmd)
	{
		shell->count++;
		fixing_cmd_red(cmd, clean);
		cmd = cmd->next;
		clean = clean->next;
	}
}

void	execute_all_cmds(t_shell *shell)
{
	t_pipexinfo	info;

	shell->cmd_ready = alloc_clean_cmd_list(shell->cmd);
	if (!shell->cmd_ready)
		return ;
	ft_bzero(&info, sizeof(t_pipexinfo));
	info.fd_in = STDIN_FILENO;
	count_and_fix_cmds(shell);
	execute_or_fork(shell, &info);
}
