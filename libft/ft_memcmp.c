/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thguimar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:11:41 by thguimar          #+#    #+#             */
/*   Updated: 2023/10/12 15:32:33 by thguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			i;

	i = 0;
	s1 = (unsigned char *) str1;
	s2 = (unsigned char *) str2;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return ((int)(s1[i] - s2[i]));
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char	str1[20] = "Apenas teste";
	char	str2[20] = "ApenaS teste";
	int		teste;

	printf("%d\n", ft_memcmp(str1, str2, 6));
	teste = memcmp(str1, str2, 5);
	printf("%d", teste);
}*/
