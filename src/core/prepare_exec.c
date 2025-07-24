/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:12:13 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/24 16:56:03 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	save_last_cmd(t_shell *shell, char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 0)
	{
		free(shell->next_last_arg);
		shell->next_last_arg = ft_strdup(args[i - 1]);
	}
}

static void	fork_loop(t_shell *shell, t_pipexinfo *info, t_cmd_r *clean)
{
	t_cmd	*cmd;

	cmd = shell->cmd;
	while (cmd)
	{
		if (cmd->next && pipe(info->fd) == -1)
			exit(1);
		if (!cmd->next)
			line_helper(info);
		info->pid = fork();
		if (info->pid == 0)
		{
			heredoc_ctrl_c(shell);
			if (info->fd[1] != -1)
				close(info->fd[0]);
			run_children(shell, clean, info, cmd);
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
		fixing_cmd_red(cmd, clean, shell);
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
