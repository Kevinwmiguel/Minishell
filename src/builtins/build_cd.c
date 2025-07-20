/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 00:11:16 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/18 18:20:34 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	check_cwd(void)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("minishell");
		write(2, "warning: current directory was deleted\n", 40);
		chdir("/home");
	}
}

char	*get_home(t_shell *shell)
{
	int		i;
	char	*home;

	i = 0;
	home = NULL;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "HOME=", 5) == 0)
		{
			home = ft_strdup(shell->env[i] + 5);
			break ;
		}
		i++;
	}
	return (home);
}

char	*get_cd_path(t_shell *shell)
{
	char	*home;

	if (!shell->cmd->args[1] || shell->cmd->args[1][0] == '\0')
	{
		home = get_home(shell);
		if (!home)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			shell->exit_code = 1;
			return (NULL);
		}
		return (home);
	}
	return (ft_strdup(shell->cmd->args[1]));
}

void	build_cd(t_shell *shell)
{
	char	*path;

	path = NULL;
	if (shell->cmd->args[2])
	{
		ft_putstr_fd(" too many arguments\n", 2);
		shell->exit_code = 1;
		return ;
	}
	path = get_cd_path(shell);
	if (!path)
		return ;
	if (chdir(path) != 0)
	{
		perror("cd");
		shell->exit_code = 1;
	}
	else
		update_pwd(shell);
	free(path);
}
