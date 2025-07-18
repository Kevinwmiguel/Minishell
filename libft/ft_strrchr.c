/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thguimar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:42:19 by thguimar          #+#    #+#             */
/*   Updated: 2023/10/12 12:51:58 by thguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*str1;
	int		i;

	str1 = (char *)str;
	i = ft_strlen(str1);
	while (i > 0 && (char)c != str1[i])
		i--;
	if ((char)c == str1[i])
		return (&str1[i]);
	return (0);
}
/*
int main(void)
{
	char    str[30] = "Apenas testando se funciona";
	printf("%s", ft_strrchr(str, 's'));
}*/
