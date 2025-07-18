/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joanda-s <joanda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:09:03 by thguimar          #+#    #+#             */
/*   Updated: 2024/08/20 16:50:09 by joanda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	long unsigned int	i;

	i = 0;
	while (s && s[i] != '\0')
	{
		i++;
	}
	return (i);
}
/*
int	main(void)
{
	char s1[] = "caracteressao15";
	printf("%li\n", ft_strlen(s1));
	printf("%li\n", strlen(s1));
}*/
