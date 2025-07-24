/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:49:40 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/24 13:21:55 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

volatile sig_atomic_t	g_heredoc_interrupted;

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
}

void	set_heredoc_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler_here;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

static void	write_limiter_lines(t_shell *shell, int *fd, char *limiter)
{
	char	*line;
	char	*tmp;

	while (!g_heredoc_interrupted)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		tmp = expand_str(shell, line);
		write(fd[1], tmp, strlen(tmp));
		free(line);
		free(tmp);
	}
}

int	here_doc(t_shell *shell, char *limiter)
{
	int		fd[2];

	if (pipe(fd) == -1)
		exit(1);
	set_heredoc_signal();
	write_limiter_lines(shell, fd, limiter);
	close(fd[1]);
	if (g_heredoc_interrupted)
	{
		close(fd[0]);
		return (-2);
	}
	return (fd[0]);
}
