/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:36:09 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/13 01:57:49 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

// pid_t pid;

// pid = fork();
// if (pid == 0)
// {
// 	shell->is_child = 1; // Estamos no filho
// 	// Executa o comando (incluindo build_exit, se for o caso)
// }
// else
// {
// 	shell->is_child = 0; // Pai continua
// 	waitpid(pid, NULL, 0); // Aguarda o filho
// }

char	*checker_path(t_shell *shell, char **paths, char *tmp)
{
	char	*fullpath;
	int		i;

	i = 0;
	fullpath = NULL;
	if (shell->cmd->args[0][0] == '.' || shell->cmd->args[0][0] == '/')
	{
		if (access(shell->cmd->args[0], X_OK) == 0)
			return (ft_strdup(shell->cmd->args[0]));
		else
			return (NULL);
	}
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		fullpath = ft_strjoin(tmp, shell->cmd->args[0]);
		free(tmp);
		if (access(fullpath, X_OK) == 0)
			break ;
		free(fullpath);
		fullpath = NULL;
		i++;
	}
	return (fullpath);
}
