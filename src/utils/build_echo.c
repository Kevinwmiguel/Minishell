/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 01:58:50 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/13 02:20:01 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	build_echo(t_shell *shell, char **args)
{
	int		i;      // Índice para percorrer os argumentos
	int		nl;     // Flag para determinar se imprime newline
	int		fd;     // File descriptor de saída (terminal, arquivo ou pipe)

	i = 1;
	nl = 1; // Por padrão, imprime o newline
	fd = STDOUT_FILENO; // Saída padrão

	// Se há redirecionamento de saída, usamos o outfd correspondente
	if (shell->cmd && shell->cmd->redirect && shell->cmd->redirect->pipe)
		fd = shell->cmd->redirect->pipe->outfd;

	// Se o primeiro argumento é "-n", não imprime o \n no final
	if (args[1] && ft_strncmp(args[1], "-n", 3) == 0)
	{
		nl = 0;
		i++;
	}

	// Imprime todos os argumentos, separados por espaço
	while (args[i])
	{
		ft_putstr_fd(args[i], fd);
		if (args[i + 1]) // Adiciona espaço se não for o último
			ft_putstr_fd(" ", fd);
		i++;
	}

	// Se a flag nl estiver ativa, imprime uma quebra de linha no final
	if (nl)
		ft_putstr_fd("\n", fd);
}
