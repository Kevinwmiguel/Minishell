/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:11:56 by kwillian          #+#    #+#             */
/*   Updated: 2025/01/06 20:42:07 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

char	*ft_strjoin(char *s1, char *s2)
{
	int		i = 0, j = 0;
	char	*str;
	if (!s1)
		s1 = (char *)malloc(1), s1[0] = '\0';
	str = malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
	if (!str) return (NULL);
	while (s1[i]) str[i] = s1[i], i++;
	while (s2[j]) str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line = NULL;
	int			read_bytes, i = 0;

	while (1)
	{
		if (!buffer[0])
			if ((read_bytes = read(fd, buffer, BUFFER_SIZE)) <= 0)
				return (line ? line : NULL);
		buffer[read_bytes] = '\0';
		line = ft_strjoin(line, buffer);
		while (buffer[i] && buffer[i] != '\n') i++;
		if (buffer[i] == '\n')
		{
			for (int j = 0; buffer[i + 1 + j]; j++) buffer[j] = buffer[i + 1 + j];
			buffer[i + 1] = '\0';
			break ;
		}
		buffer[0] = '\0';
	}
	return (line);
}