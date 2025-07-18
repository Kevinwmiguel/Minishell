/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 23:40:23 by kwillian          #+#    #+#             */
/*   Updated: 2025/02/03 21:50:54 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	freefunc(char *buffer)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	j = 0;
	n = 0;
	while (buffer[j] != '\0')
	{
		if (n)
			buffer[i++] = buffer[j];
		if (buffer[j] == '\n')
			n = 1;
		buffer[j++] = '\0';
	}
	return (n);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	buffer[BUFFER_SIZE + 1];

	line = NULL;
	while (buffer[0] || (read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		line = ft_strjoin2(line, buffer);
		if (freefunc(buffer))
			break ;
	}
	return (line);
}

// int	main()
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("archive.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		write(1, "error", 5);
// 		return (1);
// 	}
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return 0;
// }
