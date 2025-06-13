/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:28:02 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/13 22:42:47 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

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

void	path_cleaner(char **paths)
{
	int	i;

	i = 0;
	while (paths && paths[i])
	{
		if (i == 0)
			free(paths[i] - 5);
		else
			free(paths[i]);
		i++;
	}
	if (paths)
		free(paths);
}

char	**pick_path(char **envp)
{
	char	**path;
	int		index;

	index = 0;
	path = NULL;
	while (envp && envp[index])
	{
		if (ft_strncmp(envp[index], "PATH=", 5) == 0)
		{
			path = ft_split(envp[index], ':');
			if (!path)
				path_cleaner(path);
			else
				path[0] = path[0] + 5;
			break ;
		}
		index++;
	}
	return (path);
}

void	run_child(t_shell *shell, char **argv)
{
	
	int fd[2];

	if (pipe(fd) == -1)
		exit(1);
	//ENTRADA
	if (shell->cmd->redirect->pipe->infd > 0)
		dup2(fd[0], STDIN_FILENO);
	//SAIDA
	if (shell->cmd->redirect->pipe->outfd > 0)
		dup2(fd[1], STDOUT_FILENO);
	//CLOSES
	if (shell->cmd->redirect->pipe->outfd > 0)
		close(shell->cmd->redirect->pipe->outfd);
	if (shell->cmd->redirect->pipe->infd > 0)
		close(shell->cmd->redirect->pipe->infd);
	char *fullpath = get_path(shell->cmd->args[0], shell->env);
	printf("fullpath %s\n", fullpath);
	execve(fullpath, argv, shell->env);
	perror("execve: ");
	exit(1);
}

void	exec_comm(char **argv, t_shell *shell)
{
	int	processor;

	processor = fork();
	if (processor == 0)
	{
		signal_search(CHILD);
		run_child(shell, argv);
	}
	else
	{
		waitpid(processor, NULL, 0);
		build_exit(shell);
	}
}

// void	exec_comm(char **argv, t_shell *shell)
// {
// 	char	*fullpath;
// 	int		flag;
// 	char	**paths;
// 	char	*tmp;

	
// 	if (!argv || !argv[0])
// 		exit(1);
// 	paths = pick_path(shell->env);
// 	tmp = NULL;
//     printf("envp 0 %s\n", shell->env[0]);
// 	flag = builtins(argv[0]);
// 	fullpath = checker_path(shell, paths, tmp);

//     printf("fullpath %s\n", fullpath);
//     exit(1);
// 	free_split(paths);
// 	if (!fullpath && flag == 0)
// 		exit(1);
// 	if (flag > 0)
// 	{
// 		builtins_dealer(shell);
// 		exit(0);
// 	}
// 	else
// 	{
// 		execve(fullpath, argv, shell->env);
// 		exit(1);
// 	}
	
// }
