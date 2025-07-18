/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:44:05 by thguimar          #+#    #+#             */
/*   Updated: 2025/07/01 00:39:54 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"

// char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
// {
// 	size_t	i;
// 	size_t	c;
// 	size_t	n_len;
// 	char	*hay;

// 	i = 0;
// 	hay = (char *)haystack;
// 	n_len = ft_strlen(needle);
// 	if (n_len == 0 || haystack == needle)
// 		return (hay);
// 	while (hay[i] != '\0' && i < len)
// 	{
// 		c = 0;
// 		while (hay[i + c] != '\0' && needle[c] != '\0'
// 			&& hay[i + c] == needle[c] && i + c < len)
// 			c++;
// 		if (c == n_len)
// 			return (hay + i);
// 		i++;
// 	}
// 	return (0);
// }

/*
int	main(void)
{
	char	hay[30] = "lorem ipsum dolor sit amet";

	printf("%s", ft_strnstr(hay, "dolor", 20));
}*/
