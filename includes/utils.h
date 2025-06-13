/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:40:04 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/13 21:41:58 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

//UTILS
void	builtins_dealer(t_shell *shell);
void	free_dptr(char **dptr);
void	execute_all_cmds(t_shell *shell);
int		builtins(char *str);
char	*checker_path(t_shell *shell, char **paths, char *tmp);
void	exec_comm(char **argv, t_shell *shell);
void	free_split(char **split);

//alocation
int		mlc_size(int j, char **mlc);
char	**dptr_dup(char	**dptr);

//Cleaner
void	final_cleaner(t_shell *shell);

//ECHO

void	build_echo(t_shell *shell, char **args);

//CD

void	build_cd(t_shell *shell);

//PWD
void	build_pwd(t_shell *shell);

//ENV

void	build_env(t_shell *shell);

//EXPORT
char    **build_export(char **env);

//UNSET
void	build_unset(t_shell *shell);

//EXIT
void	build_exit(t_shell *shell);

//PATHS
char	*get_directory_path(char *path);
char	*get_path(char *cmd, char **envp);

//SIGNALS
void	signal_search(t_sig_t t);

#endif