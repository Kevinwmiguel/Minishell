/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:40:04 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/19 20:15:17 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

//UTILS
void	builtins_dealer(t_shell *shell, t_pipexinfo *info);
void	free_dptr(char **dptr);
void	execute_all_cmds(t_shell *shell);
int		builtins(char *str);
char	*checker_path(t_shell *shell, char **paths, char *tmp);
void	fork_comms(char **argv, t_shell *shell, t_pipexinfo *info);
void	free_split(char **split);
void	run_child(t_shell *shell, char **argv, t_pipexinfo *info);
int		here_doc(char *limiter);
void	handle_redirection_left_input(t_cmd *cmd);

//PIPES
void	fixing_cmd_red(t_cmd *cmd);

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
void	update_pwd(t_shell *shell);

//ENV

void	build_env(t_shell *shell);

//EXPORT
char	**build_export(t_shell *shell);
void	handle_export(t_shell *shell);

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