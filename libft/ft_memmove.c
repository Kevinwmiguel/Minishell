/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thguimar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:34:30 by thguimar          #+#    #+#             */
/*   Updated: 2023/10/11 13:00:25 by thguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest > src)
	{
		while (n-- > 0)
		{
			((unsigned char *)dest)[n]
				= ((unsigned char *)src)[n];
		}
	}
	else
	{
		while (i < n)
		{
			((unsigned char *)dest)[i]
				= ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}
/*
int	main(void)
{
	char	dest[40] = "gugugagatyutyutyuttr7";
	char	src[20] = "peidou";

	printf("%s\n", dest);
	ft_memmove(dest, src, 7);
	printf("%s", dest);
}*/
