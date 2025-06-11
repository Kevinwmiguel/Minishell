/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_dealer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:57:27 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/11 02:48:56 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/builtins.h"

int	count_without_quotes(const char *str, int i)
{
	int		len;
	char	c;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i++];
			while (str[i] && str[i] != c)
			{
				i++;
				len++;
			}
			if (str[i])
				i++;
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

char	*malloc_no_quotes(const char *str)
{
	int		len;
	char	*res;

	len = count_without_quotes(str, 0);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	return (res);
}

void	copy_without_quotes(char *dest, const char *src)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] == '\'' || src[i] == '"')
		{
			quote = src[i++];
			while (src[i] && src[i] != quote)
				dest[j++] = src[i++];
			if (src[i])
				i++;
		}
		else
			dest[j++] = src[i++];
	}
	dest[j] = '\0';
}

char	*remove_quotes(const char *str)
{
	char	*res;

	if (!str)
		return (NULL);
	res = malloc_no_quotes(str);
	if (!res)
		return (NULL);
	copy_without_quotes(res, str);
	return (res);
}
