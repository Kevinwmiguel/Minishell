/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:37:03 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/09 21:27:51 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/builtins.h"

char	*checker_path(t_pipesort *piped, char **paths, char *tmp)
{
	char	*fullpath;
	int		i;

	i = 0;
	fullpath = NULL;
	if (piped->content[0][0] == '.' || piped->content[0][0] == '/')
	{
		if (access(piped->content[0], X_OK) == 0)
			return (ft_strdup(piped->content[0]));
		else
			return (NULL);
	}
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		fullpath = ft_strjoin(tmp, piped->content[0]);
		free(tmp);
		if (access(fullpath, X_OK) == 0)
			break ;
		free(fullpath);
		fullpath = NULL;
		i++;
	}
	return (fullpath);
}

void	exec_comm(char **cmd_args, char **envp, \
	t_pipesort *piped, t_shell *utils)
{
	char	*fullpath;
	int		flag;
	char	**paths;
	char	*tmp;

	if (!cmd_args || !cmd_args[0])
		exit(1);
	paths = pick_path(envp);
	tmp = NULL;
	flag = builtins(piped->content[0], utils, -1);
	fullpath = checker_path(piped, paths, tmp);
	path_cleaner(paths);
	if (!fullpath && flag == 0)
		inform_path_error();
	if (flag > 0)
	{
		exec_builtin(flag, piped->content, utils->envr, utils);
		exit(0);
	}
	else
	{
		execve(fullpath, cmd_args, envp);
		exit(1);
	}
}

void	child_p(t_files *file, t_pipesort *piped, t_shell *utils, t_fdinfo info)
{
	if (piped->heredoc_fd > 0)
		dup2(piped->heredoc_fd, STDIN_FILENO);
	else if (info.i > 0)
		dup2(info.fd_in, STDIN_FILENO);
	if (piped->outfd > 0)
		dup2(piped->outfd, STDOUT_FILENO);
	else if (info.i < info.pipe_count - 1)
		dup2(info.fd_write, STDOUT_FILENO);
	if (piped->heredoc_fd > 0)
		close(piped->heredoc_fd);
	if (info.fd_in != -1)
		close(info.fd_in);
	if (info.i < info.pipe_count - 1)
	{
		close(info.fd_read);
		close(info.fd_write);
	}
	exec_comm(file->cmds[info.i], file->envp, piped, utils);
}

void	parent_process(t_pipexinfo *px, t_pipesort **piped)
{
	if (px->fd_in != -1)
		close(px->fd_in);
	if (px->i < px->pipe_counts - 1)
	{
		close(px->fd[1]);
		px->fd_in = px->fd[0];
	}
	waitpid(px->pid, NULL, 0);
	*piped = (*piped)->next;
}

void	main3pipex(t_files *file, t_pipesort *piped, t_shell *utils)
{
	t_pipexinfo	px;

	init_pipexinfo(&px, piped);
	while (px.i < px.pipe_counts)
	{
		utils->index++;
		if (px.i < px.pipe_counts - 1)
			if (pipe(px.fd) == -1)
				exit(1);
		px.pid = fork();
		if (px.pid == 0)
			child_p(file, piped, utils,
				(t_fdinfo){px.fd_in, px.fd[0], px.fd[1], px.i, px.pipe_counts});
		else
			parent_process(&px, &piped);
		px.i++;
	}
	//final_cleaner(utils);
	//free(file->paths);
	//free_dptr(utils->envr, 0);
	//final_cleaner9(file);
}
