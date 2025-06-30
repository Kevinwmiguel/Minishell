/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:00:35 by thguimar          #+#    #+#             */
/*   Updated: 2025/07/01 00:45:11 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int			len;
	char		*ptr;
	const char	*nmrs;

	len = ft_len(n);
	ptr = malloc(sizeof (char) * (len + 1));
	nmrs = "0123456789";
	if (!ptr)
		return (0);
	ptr[len] = '\0';
	if (n == 0)
		ptr[0] = '0';
	if (n < 0)
		ptr[0] = '-';
	while (n)
	{
		if (n > 0)
			ptr[--len] = nmrs[n % 10];
		else
			ptr[--len] = nmrs[n % 10 * -1];
		n /= 10;
	}
	return (ptr);
}
/*
int	main(void)
{
	printf("%s", ft_itoa(4242));
}*/
