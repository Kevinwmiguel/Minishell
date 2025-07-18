/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thguimar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:31:53 by thguimar          #+#    #+#             */
/*   Updated: 2023/10/13 14:42:44 by thguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	n;

	i = 0;
	s = 1;
	n = 0;
	while ((str[i] > 8 && str[i] < 14) || (str[i] == 32))
		i++;
	while (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			s = s * (-1);
		if ((str[i] == 45 || str[i] == 43) && (str[i + 1] == 45
				|| str[i + 1] == 43))
			return (0);
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		n = (n * 10) + (str[i] - 48);
		i++;
	}
	return (n * s);
}
/*
int	main(void)
{
	char str[] = "\n      +-123";
	printf("%d\n", ft_atoi(str));
	printf("%d", atoi(str));
}*/
