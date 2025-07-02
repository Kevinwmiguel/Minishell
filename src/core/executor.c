/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:28:02 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/02 00:26:21 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	executor(t_shell *shell, char **argv)
{
	int		flag;
	char	*fullpath;

	if (!argv || !argv[0])
		exit(1);
	flag = builtins(argv[0]);
	if (flag > 0)
	{
		builtins_analyzer(shell, flag);
		exit(1);
	}
	else
	{
		fullpath = get_path(argv[0], shell->env);
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
			run_children(shell, clean->args, info);
		}
		line_helper2(info);
		info->fd_in = info->fd[0];
		cmd = cmd->next;
	}
	while (wait(NULL) != -1)
		;
}

t_cmd_r *alloc_clean_cmd_list(t_cmd *cmd)
{
	t_cmd_r *head = NULL;
	t_cmd_r *curr = NULL;
	t_cmd_r *new;

	while (cmd)
	{
		new = malloc(sizeof(t_cmd_r));
		if (!new)
			return (NULL); // você pode adicionar um free depois se quiser
		new->args = NULL;
		new->next = NULL;
		if (!head)
			head = new;
		else
			curr->next = new;
		curr = new;
		cmd = cmd->next;
	}
	return (head);
}

void	execute_all_cmds(t_shell *shell)
{
	t_pipexinfo	info;
	t_cmd		*cmd;
	t_cmd_r		*clean;

	shell->cmd_ready = alloc_clean_cmd_list(shell->cmd);
	if (!shell->cmd_ready)
		return ;
	clean = shell->cmd_ready;
	cmd = shell->cmd;
	ft_bzero(&info, sizeof(t_pipexinfo));
	info.fd_in = STDIN_FILENO;
	shell->count = 0;
	while (cmd)
	{
		shell->count++;
		fixing_cmd_red(cmd, clean);
		cmd = cmd->next;
		clean = clean->next;
	}
	clean = shell->cmd_ready;
	if (shell->count == 1)
	{
		builtins_dealer(shell, &info, clean);
		free_cmdr(clean);
		shell->cmd_ready = NULL;
		return;
	}
	else
	{
		fork_loop(shell, &info, clean);
		free_cmdr(clean);
		shell->cmd_ready = NULL;
	}
}
