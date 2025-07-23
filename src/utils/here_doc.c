/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:49:40 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/23 15:22:38 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	is_heredoc(t_cmd *cmd)
{
	t_red	*redir;

	redir = cmd->redirect;
	while (redir)
	{
		if (redir->type == HEREDOC)
			return (1);
		redir = redir->next;
	}
	return (0);
}

void	free_cmds(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->args)
			free_split(cmd->args);
		if (cmd->redirect)
			free_redirections(cmd->redirect);
		free(cmd);
		cmd = tmp;
	}
}

void	here_signal(int signal, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "ssssss\n", 5);
		exit(130);
	}
}

void	heredoc_sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		close(STDIN_FILENO);
	}
}

void	heredoc_child(char *limiter, int write_fd, t_shell *shell)
{
	char	*line;

	signal(SIGINT, heredoc_sigint_handler);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		write(write_fd, line, strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	close(write_fd);
	close_extra_fds();
	final_cleaner(shell);
	exit(130);
}

int	here_doc(char *limiter, t_shell *shell)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	status = 0;
	if (pipe(fd) == -1)
		return (-1);

	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		heredoc_child(limiter, fd[1], shell);

	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close_extra_fds();
		return (-2);
	}
	return (fd[0]);
}
