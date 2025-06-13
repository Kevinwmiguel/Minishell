/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 01:59:57 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/13 13:37:31 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	build_pwd(t_shell *shell)
{
	char	cwd[4096]; // Buffer para armazenar o caminho atual
	int		fd;        // File descriptor para saída

	fd = STDOUT_FILENO; // Por padrão, escreve no terminal

	// Se houver redirecionamento, atualiza o fd
	// if (shell->cmd && shell->cmd->redirect && shell->cmd->redirect->pipe)
	// 	fd = shell->cmd->redirect->pipe->outfd;

	(void)shell;
	// getcwd escreve o diretório atual em cwd
	if (getcwd(cwd, 4096))
	{
		ft_putstr_fd(cwd, fd);     // Escreve o caminho no destino
		ft_putstr_fd("\n", fd);    // Adiciona uma quebra de linha
	}
}
