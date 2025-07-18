/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thguimar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:13:08 by thguimar          #+#    #+#             */
/*   Updated: 2023/10/11 13:01:18 by thguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	int				i;

	str1 = (unsigned char *)dest;
	str2 = (unsigned char *)src;
	i = 0;
	while (n > 0)
	{
		str1[i] = str2[i];
		n--;
		i++;
	}
	return (str1);
}
/*
int	main(void)
{
	char	dest[20] = "eu te odeio";
	char	src[20] = "eu te amo";

	printf("%s\n", dest);
	ft_memcpy(dest, src, 8);
	printf("%s", dest);
}*/
