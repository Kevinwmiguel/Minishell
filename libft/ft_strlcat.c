/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thguimar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:26:24 by thguimar          #+#    #+#             */
/*   Updated: 2023/10/11 12:48:38 by thguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (size == 0)
		return (i + ft_strlen(src));
	while (dest[i] != '\0' && i < size)
		i++;
	j = 0;
	while (src[j] != '\0' && (j + i) < (size - 1))
	{
		dest[i + j] = src[j];
		j++;
	}
	if (i != size)
		dest[i + j] = '\0';
	return (i + ft_strlen(src));
}
/*
int	main(void)
{
	char	dest[20] = "a";
//	char	src[20] = "mente gay!";

	printf("%ld", ft_strlcat(dest, "lorem ipsum", 15));
}*/
