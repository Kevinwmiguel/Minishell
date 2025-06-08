/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:00:48 by kwillian          #+#    #+#             */
/*   Updated: 2024/04/18 16:26:29 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num_elements, size_t element_size)
{
	void	*memo;

	memo = malloc(num_elements * element_size);
	if (!memo)
		return (NULL);
	ft_bzero(memo, num_elements * element_size);
	return (memo);
}
