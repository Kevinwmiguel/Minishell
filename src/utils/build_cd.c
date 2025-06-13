/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 00:11:16 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/13 13:40:26 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

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

void	build_cd(t_shell *shell)
{
	char	*path = NULL;
	char	*home;

	if (!shell->cmd->args[1] || shell->cmd->args[1][0] == '\0')
	{
		home = get_home(shell);
		if (!home)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return ;
		}
		path = home;
	}
	else
		path = ft_strdup(shell->cmd->args[1]);
	if (chdir(path) != 0)
		perror("minishell: cd");
	else
	{
		build_pwd(shell);
		// Aqui você poderia atualizar PWD e OLDPWD
		// Exemplo: update_pwd(shell);
	}
	if (shell->cmd->args[1])
		free(path);
}
