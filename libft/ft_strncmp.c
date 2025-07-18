/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thguimar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:56:54 by thguimar          #+#    #+#             */
/*   Updated: 2023/10/11 17:54:23 by thguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t			i;
	unsigned char	s1;
	unsigned char	s2;

	i = 0;
	while (i < n)
	{
		s1 = (unsigned char)str1[i];
		s2 = (unsigned char)str2[i];
		if (s1 != s2)
			return ((int)(s1 - s2));
		else if (s1 == 0)
			return (0);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char	str1[20] = "abc";
	char	str2[20] = "abcdef";

	printf("%d", ft_strncmp(str1, str2, 5));
//	printf("%d", strncmp(str1, str2, 5));
}*/
