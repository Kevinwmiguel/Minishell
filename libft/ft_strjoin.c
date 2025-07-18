/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joanda-s <joanda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:06:29 by thguimar          #+#    #+#             */
/*   Updated: 2024/08/20 16:51:47 by joanda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*rtn;

	i = 0;
	j = 0;
	rtn = malloc(sizeof (char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!rtn)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		rtn[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2 && s2[i] != '\0')
	{
		rtn[j] = s2[i];
		i++;
		j++;
	}
	rtn[j] = '\0';
	return ((char *)rtn);
}
/*
int	main(void)
{
	printf("%s", ft_strjoin("voce e incrivel", "mente gay"));
}*/
