/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:49:40 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/23 21:03:40 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

volatile sig_atomic_t g_heredoc_interrupted = 0;

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
		write(STDOUT_FILENO, "\n", 1);
		exit(130);
	}
}

void	sigint_handler_here(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_heredoc_interrupted = 1;
	// não usa _exit aqui, queremos apenas marcar a flag
}

void	set_heredoc_signal(void)
{
	struct sigaction sa;

	sa.sa_handler = sigint_handler_here;
	sa.sa_flags = 0; // <---- IMPORTANTE: NÃO usa SA_RESTART!
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

int	here_doc(t_shell *shell, char *limiter)
{
	char	*line;
	int		fd[2];
	char	*tmp;

	if (pipe(fd) == -1)
		exit(1);
	set_heredoc_signal();
	while (1)
	{
		if (g_heredoc_interrupted)
			break;
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break;
		if (strncmp(line, limiter, strlen(limiter)) == 0
			&& line[strlen(limiter)] == '\n'
			&& line[strlen(limiter) + 1] == '\0')
		{
			free(line);
			break;
		}
		tmp = expand_str(shell, line);
		write(fd[1], tmp, strlen(tmp));
		free(line);
		free(tmp);
	}

	close(fd[1]);

	if (g_heredoc_interrupted)
	{
		close(fd[0]);
		return (-2); // <- você pode usar essa condição no pai
	}

	return (fd[0]);
}
