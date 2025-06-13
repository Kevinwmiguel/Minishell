/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:01:41 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/13 19:41:11 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char			*nova;
	unsigned int	i;
	unsigned int	j;
	int				size;

	i = -1;
	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	nova = (char *)malloc((size + 1) * sizeof(char));
	if (!nova)
		return (NULL);
	while (s1[++i] != '\0')
		nova[i] = s1[i];
	j = 0;
	while (s2[j] != '\0')
	{
		nova[i] = s2[j];
		j++;
		i++;
	}
	nova[i] = '\0';
	return (nova);
}
