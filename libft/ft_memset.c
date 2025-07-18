/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thguimar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:17:40 by thguimar          #+#    #+#             */
/*   Updated: 2023/10/06 15:03:39 by thguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int l, size_t n)
{
	unsigned char	*c;

	c = s;
	while (n > 0)
	{
		c[n - 1] = l;
		n--;
	}
	return (s);
}
/*
int	main(void)
{
	unsigned char	str[16] = "gorila";
	printf("%s\n", (char *)ft_memset(str, '*', 15));
	printf("%s", (char *)memset(str, '*', 15));
}*/
