/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thguimar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:43:57 by thguimar          #+#    #+#             */
/*   Updated: 2023/10/12 15:52:33 by thguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*str1;

	str1 = (unsigned char *)str;
	c = (unsigned char)c;
	while (n)
	{
		if (*str1 == c)
			return ((unsigned char *)str1);
		str1++;
		n--;
	}
	return (NULL);
}
