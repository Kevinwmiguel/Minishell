/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:28:02 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/13 17:54:46 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

static void	exec_builtin(t_shell *sh, t_cmd_r *cl, int flag)
{
	int	code;

	if (sh->exit_code == 126 || sh->exit_code == 127)
	{
		code = sh->exit_code;
		free_token_list(sh);
		close_extra_fds();
		close_redirections(sh->cmd);
		final_cleaner(sh);
		exit(code);
	}
	if (!ft_strncmp(cl->args[0], "export", 7) && sh->count > 1 && !cl->args[1])
		export_print(sh->exp);
	else
		builtins_analyzer(sh, flag, cl->args);
	code = sh->exit_code;
	free_token_list(sh);
	close_extra_fds();
	close_redirections(sh->cmd);
	final_cleaner(sh);
	exit(code);
}

void	non_path(t_shell *sh, char *full)
{
	printf("full %s", full);
	perror("command not found");
	final_cleaner(sh);
	exit(127);
}

static void	exec_external(t_shell *sh, t_cmd_r *cl)
{
	char	*full;
	int		code;

	close_extra_fds();
	full = get_path(cl->args[0], sh->env);
	if (!full)
		non_path(sh, full);
	if (sh->exit_code == 126 || sh->exit_code == 127)
	{
		code = sh->exit_code;
		free(full);
		free_token_list(sh);
		close_extra_fds();
		close_redirections(sh->cmd);
		final_cleaner(sh);
		exit(code);
	}
	else
	{
		execve(full, cl->args, sh->env);
		perror("execve: ");
		free(full);
		final_cleaner(sh);
		exit(1);
	}
}

void	executor(t_shell *shell, t_cmd_r *clean)
{
	int	flag;

	if (!clean->args || !clean->args[0])
		exit(1);
	flag = builtins(clean->args[0]);
	if (flag > 0)
		exec_builtin(shell, clean, flag);
	else
		exec_external(shell, clean);
}
