/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:40:04 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/03 13:10:00 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include "../get_next_line/get_next_line.h"

//MINISHELL
void	init(t_shell *shell, char **env);
int		run(t_shell *shell);

//CLOSES
void	close_redirections(t_cmd *cmd);

//GETNEXTLINE
char	*get_next_line(int fd);

//UTILS
void	free_cmdr(t_cmd_r *cmd);
void prepare_all_output_files(t_cmd *cmd);
void	import_args_to_clean(t_cmd *cmd, t_cmd_r *clean);
char	*special_cleaner(const char *s1, const char *s2, t_shell *shell);
void	builtins_dealer(t_shell *shell, t_pipexinfo *info, t_cmd_r *clean);
void	free_dptr(char **dptr);
void	execute_all_cmds(t_shell *shell);
int		builtins(char *str);
char	*checker_path(t_shell *shell, char **paths, char *tmp);
void	run_child(char **argv, t_shell *shell, t_pipexinfo *info);
void	run_children(t_shell *shell, char **argv, t_pipexinfo *info);
void	free_split(char **split);
int		here_doc(char *limiter);
void	handle_redirection_left_input(t_cmd *cmd);
void	handle_redirection_right_input(t_cmd *cmd);
int		dptr_len(char **ptr);
char	**dptr_dup_replace(char **env, char *new_entry, int index);
char	**dptr_dup_add(char **env, char *new_entry);
char	*strjoin_free(char *s1, char *s2);
int		is_valid_identifier(char *str);

//builtins
void	builtins_analyzer(t_shell *shell, int flag);

//PIPES
void	fixing_cmd_red(t_cmd *cmd, t_cmd_r *clean);
void	find_last_output_redir(t_cmd *cmd, \
	int *last_index, char **redir_type);
void	open_last_output_file(t_cmd *cmd, \
	int last_index, char *redir_type);
void	remove_last_redir_pair(t_cmd *cmd, int index);
void	remove_redir_pair(t_cmd *cmd, int index);
int		create_empty_output_file(char *type, char *filename);
int		find_input_file_index(char **content, int i);
int		find_next_double_left_index(t_cmd *cmd, int start);

//alocation
int		mlc_size(int j, char **mlc);
char	**dptr_dup(char	**dptr);

//Cleaner
void	final_cleaner(t_shell *shell);
void	free_split(char **arr);
char	*special_cleaner(const char *s1, const char *s2, t_shell *shell);

//ECHO

void	build_echo(t_shell *shell, char **args);

//CD

void	build_cd(t_shell *shell);

//PWD
void	build_pwd(t_shell *shell);
void	update_pwd(t_shell *shell);

//ENV

void	build_env(t_shell *shell);
char	**add_or_replace_env(char **env, char *new_entry);

//EXPORT
char	**build_export(t_shell *shell);
void	handle_export(t_shell *shell, t_cmd_r *clean);
char	**add_or_replace_exp(char **exp, char *new_entry);
void	update_env_export(t_shell *shell, char **args);
char	**merge_exp_lists(char **old, char **new, char **env);
int		find_in_env(char **env, const char *key);
char	*join_export(char *name, char *value);

//UNSET
void	build_unset(t_shell *shell);

//EXIT
void	build_exit(t_shell *shell);

//PATHS
char	*get_directory_path(char *path);
char	*get_path(char *cmd, char **envp);

//SIGNALS
void	signal_search(t_sig_t t);
void	here_signal(int signal, siginfo_t *info, void *context);

#endif