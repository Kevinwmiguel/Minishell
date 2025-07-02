/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:49:40 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/02 01:14:18 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	here_signal(int signal, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signal == SIGINT)
	{
		printf("\n");
		exit(130);
	}
}

int	here_doc(char *limiter)
{
	char	*line;
	int		fd[2];

	if (pipe(fd) == -1)
		exit(1);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		//line = ft_strjoin(line, "\n");
		if (!line)
			break ;
		if (ft_strlen(line) == ft_strlen(limiter) + 1 && \
			ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 && \
			line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}
