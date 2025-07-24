/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:01:00 by kwillian          #+#    #+#             */
/*   Updated: 2024/11/02 20:28:57 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

char	*ft_strjoin2(char *s1, char const *s2)
{
	char			*nova;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	nova = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!nova)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		nova[i] = s1[i];
		i++;
	}
	j = 0;
	free(s1);
	while (s2[j] != '\0' && s2 != NULL)
	{
		nova[i++] = s2[j++];
		if (s2[j - 1] == '\n')
			break ;
	}
	nova[i] = '\0';
	return (nova);
}
