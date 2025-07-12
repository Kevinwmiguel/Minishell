/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:28:02 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/11 12:41:37 by jmehmy           ###   ########.fr       */
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

static void	exec_external(t_shell *sh, t_cmd_r *cl)
{
	char	*full;

	close_extra_fds();
	full = get_path(cl->args[0], sh->env);
	if (!full)
	{
		perror("command not found");
		final_cleaner(sh);
		exit(127);
	}
	if(access(full, F_OK) == 0 && access(full, X_OK) != 0)
	{
		perror(full);
		free(full);
		final_cleaner(sh);
		exit(126);
	} 
	else if (access(full, F_OK) != 0)
	{
		ft_putstr_fd(full, 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
		free(full);
		final_cleaner(sh);
		exit(127);
	}
	execve(full, cl->args, sh->env);
	perror("execve: ");
	free(full);
	final_cleaner(sh);
	exit(1);
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
