/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:28:02 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/24 21:01:25 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

static void	exec_builtin(t_shell *sh, t_cmd_r *cl, int flag)
{
	int	code;

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

void	non_path(t_shell *sh, char *full, t_cmd_r *cl)
{
	ft_putstr_fd(cl->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	if (full)
		free(full);
	final_cleaner(sh);
	exit(127);
}

static void	check_access_and_errors(t_shell *sh, char *full)
{
	if (sh->mistake)
	{
		free(full);
		final_cleaner(sh);
		//ft_putstr_fd("file not provided\n", 2);
		exit(1);
	}
	file_checker(sh, full);
}

static void	exec_external(t_shell *sh, t_cmd_r *cl)
{
	char	*full;

	close_extra_fds();
	if (!ft_strchr(cl->args[0], '/'))
	{
		full = get_path(cl->args[0], sh->env);
		if (!full || ft_strcmp2(full, cl->args[0]) == 0)
			non_path(sh, full, cl);
	}
	else
	{
		full = ft_strdup(cl->args[0]);
		if (!full)
		{
			perror("malloc");
			final_cleaner(sh);
			exit(1);
		}
	}
	check_access_and_errors(sh, full);
	execve(full, cl->args, sh->env);
	perror("execve");
	free(full);
	final_cleaner(sh);
	exit(1);
}

void	executor(t_shell *shell, t_cmd_r *clean)
{
	int	flag;

	finder_and_update(shell);
	if (!clean->args || !clean->args[0])
		exit(1);
	flag = builtins(clean->args[0]);
	if (flag > 0)
		exec_builtin(shell, clean, flag);
	else
		exec_external(shell, clean);
}
