/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 23:38:44 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/18 00:04:35 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	builtins(char *str)
{
	if (ft_strncmp(str, "echo", 4) == 0)
		return (1);
	if (ft_strncmp(str, "cd", 2) == 0)
		return (2);
	if (ft_strncmp(str, "pwd", 3) == 0)
		return (3);
	if (ft_strncmp(str, "export", 6) == 0)
		return (4);
	if (ft_strncmp(str, "unset", 5) == 0)
		return (5);
	if (ft_strncmp(str, "env", 3) == 0)
		return (6);
	if (ft_strncmp(str, "exit", 4) == 0)
		return (7);
	return (0);
}

void	handle_special_builtins(char **argv, t_shell *shell)
{
	int	ret;

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

void	handle_export(t_shell *shell)
{
	int		i;

	i = 0;
	free_dptr(shell->exp);
	shell->exp = build_export(shell->env);
	if (!shell->exp)
		return ;
	while (shell->exp[i])
	{
		write(1, shell->exp[i], ft_strlen(shell->exp[i]));
		write(1, "\n", 1);
		i++;
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
void	builtins_dealer(t_shell *shell, t_pipexinfo *info)
{
	if (shell->count == 1)
	{
		if (ft_strncmp(shell->cmd->args[0], "export", 6) == 0 && \
			shell->cmd->redirect == NULL)
			handle_export(shell);
		else if ((ft_strncmp(shell->cmd->args[0], "cd", 2) == 0) || \
				(ft_strncmp(shell->cmd->args[0], "unset", 5) == 0) || \
				(ft_strncmp(shell->cmd->args[0], "exit", 4) == 0))
			handle_special_builtins(shell->cmd->args, shell);
		if (builtins(shell->cmd->args[0]) > 0)
			handle_normal_builtins(shell->cmd->args, shell);
		else
			fork_comms(shell->cmd->args, shell, info);
	}
	else
		fork_comms(shell->cmd->args, shell, info);
}

void	execute_all_cmds(t_shell *shell)
{
	t_cmd		*hold;
	t_pipexinfo	info;
	t_cmd		*hold2;

	info.fd_in = STDIN_FILENO;
	hold = shell->cmd;
	hold2 = shell->cmd;
	shell->count = 0;
	while (hold)
	{
		shell->count++;
		hold = hold->next;
	}
	hold = hold2;
	while (hold)
	{
		builtins_dealer(shell, &info);
		hold = hold->next;
	}
}
