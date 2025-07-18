/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thguimar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:32:28 by thguimar          #+#    #+#             */
/*   Updated: 2023/10/11 16:15:21 by thguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str != '\0' && (char)c != *str)
		str++;
	if ((char)c == *str)
		return (str);
	return (0);
}
/*
int main(void)
{
	char    str[30] = "Apenas testando se funciona";
	printf("%s", ft_strchr(str, 't'));
}*/
