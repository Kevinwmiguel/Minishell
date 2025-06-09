/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:18:22 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/09 19:43:43 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/builtins.h"

void	close_inout(t_files *file)
{
	if (file->infile >= 0)
		close(file->infile);
	if (file->outfile >= 0)
		close(file->outfile);
}
