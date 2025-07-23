/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:49:40 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/18 18:58:05 by kwillian         ###   ########.fr       */
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

static int	handle_heredoc_input(t_shell *shell, char *limiter, int write_fd)
{
	char *line;
	char *tmp;
	char *str;

	while (1)
	{
		tmp = NULL;
		line = readline("> ");
		if (!line)
		{
			write(1, "\n", 1);
			freedom(shell);
			break ;
		}
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& ft_strlen(line) == ft_strlen(limiter))
		{
			free(line);
			break ;
		}
		tmp = expand_str(shell, line);
		str = ft_strjoin(tmp, "\n");
		if (!str)
		{
			free(line);
			free(tmp);
			break ;
		}
		write(write_fd, str, ft_strlen(str));
		free(str);
		free(line);
		free(tmp);
	}
	close(write_fd);
	return (0);
}

int here_doc(t_shell *shell, char *limiter)
{
	int fd[2];
	pid_t pid;
	int status;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		handle_heredoc_child(shell, limiter, fd);
	else
	{
		signal_search(IGNORE);
		close(fd[1]);
		waitpid(pid, &status, 0);

		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			shell->exit_code = 130;
			close(fd[0]);
			return (-1);
		}
		return fd[0];
	}
}
