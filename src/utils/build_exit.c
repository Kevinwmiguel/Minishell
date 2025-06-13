/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:31:38 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/13 22:29:47 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	build_exit(t_shell *shell)
{
	char	**args = shell->cmd->args; // Pega os argumentos do comando atual (ex: ["exit", "42"])
	int		status = 0;                // Código de saída padrão (caso nenhum seja fornecido)
	//int		i = 0;                     // Índice para percorrer a string de argumento

	ft_putendl_fd("\nexit\n", STDOUT_FILENO); // Exibe "exit" no terminal como feedback visual
	final_cleaner(shell);  // Libera toda a memória alocada e estrutura do shell
	exit(1); 
	// if (!args[1]) // Se não há segundo argumento (ex: só "exit")
	// {
	// 	final_cleaner(shell);  // Libera toda a memória alocada e estrutura do shell
	// 	exit(0);               // Encerra o processo com status 0 (sucesso)
	// }
	// Verifica se todos os caracteres do argumento são dígitos
	// while (args[1][i])
	// {
	// 	if (!ft_isdigit(args[1][i])) // Se encontrar um caractere não numérico
	// 	{
	// 		ft_putendl_fd("numeric argument required", STDERR_FILENO); // Imprime erro
	// 		final_cleaner(shell);   // Limpa recursos
	// 		exit(2);                // Encerra com status 2 (erro de uso)
	// 	}
	// 	i++;
	// }
	status = ft_atoi(args[1]); // Converte o argumento numérico para inteiro
	final_cleaner(shell);      // Limpa memória antes de sair
	exit(status);              // Encerra com o status fornecido (ex: exit 42 → retorna 42)
}

