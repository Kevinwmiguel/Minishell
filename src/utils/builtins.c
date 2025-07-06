/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 23:38:44 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/06 15:00:49 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	builtins_analyzer(t_shell *shell, int flag, char **args)
{
	(void)shell;
	if (flag == 1)
		build_echo(shell, args);
	if (flag == 2)
		build_cd(shell);
	if (flag == 3)
		build_pwd(shell);
	if (flag == 4)
		build_export(shell);
	if (flag == 5)
		build_unset(shell);
	if (flag == 6)
		build_env(shell);
	if (flag == 7)
		build_exit(shell);
}

int	builtins(char *str)
{
	if (ft_strncmp(str, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(str, "cd", 3) == 0)
		return (2);
	if (ft_strncmp(str, "pwd", 4) == 0)
		return (3);
	if (ft_strncmp(str, "export", 7) == 0)
		return (4);
	if (ft_strncmp(str, "unset", 6) == 0)
		return (5);
	if (ft_strncmp(str, "env", 4) == 0)
		return (6);
	if (ft_strncmp(str, "exit", 5) == 0)
		return (7);
	return (0);
}

void	handle_special_builtins(char **argv, t_shell *shell)
{
	int	ret;

	(void)argv;
	ret = builtins(argv[0]);
	if (ret != 0)
	{
		if (ret == 2)
			build_cd(shell);
		if (ret == 5)
			build_unset(shell);
		if (ret == 7)
		{
			build_exit(shell);
			exit(1);
		}
	}
}

void	handle_normal_builtins(char **argv, t_shell *shell)
{
	int	ret;

	ret = builtins(argv[0]);
	if (ret != 0)
	{
		if (ret == 1)
			build_echo(shell, argv);
		if (ret == 3)
			build_pwd(shell);
		if (ret == 6)
		{
			build_env(shell);
		}
	}
}

void	builtins_dealer(t_shell *shell, t_pipexinfo *info, t_cmd_r *clean)
{
	if (shell->count == 1)
	{
		if (ft_strncmp(shell->cmd->args[0], "export", 6) == 0)
		{
			handle_export(shell, clean);
			return ;
		}
		else if ((ft_strncmp(shell->cmd->args[0], "cd", 2) == 0) || \
				(ft_strncmp(shell->cmd->args[0], "unset", 5) == 0) || \
				(ft_strncmp(shell->cmd->args[0], "exit", 4) == 0))
		{
			handle_special_builtins(clean->args, shell);
			return ;
		}
	}
	run_child(clean, shell, info);
}
