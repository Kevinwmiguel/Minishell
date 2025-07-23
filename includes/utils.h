/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:40:04 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/23 00:22:45 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include "../get_next_line/get_next_line.h"
# include <limits.h>

//MINISHELL
void	init(t_shell *shell, char **env);
int		run(t_shell *shell);

//HEREDOC
int		is_heredoc(t_cmd *cmd);

//CLOSES
void	close_redirections(t_cmd *cmd);
void	get_out(t_shell *shell);
void	freedom(t_shell *shell);

//GETNEXTLINE
char	*get_next_line(int fd);

//UTILS
void	free_cmdr(t_cmd_r *cmd);
void	prepare_all_output_files(t_cmd *cmd);
void	import_args_to_clean(t_cmd *cmd, t_cmd_r *clean);
char	*special_cleaner(const char *s1, const char *s2, t_shell *shell);
void	builtins_dealer(t_shell *shell, t_pipexinfo *info, t_cmd_r *clean);
void	free_dptr(char **dptr);
void	execute_all_cmds(t_shell *shell);
int		builtins(char *str);
char	*checker_path(t_shell *shell, char **paths, char *tmp);
void	run_child(t_cmd_r *clean, t_shell *shell, t_pipexinfo *info);
void	run_children(t_shell *shell, t_cmd_r *clean, \
	t_pipexinfo *info, t_cmd *cmd);
void	free_split(char **split);
int		here_doc(char *limiter);
void	handle_redirection_left_input(t_cmd *cmd, t_shell *shell);
void	handle_redirection_right_input(t_cmd *cmd, t_shell *shell);
int		dptr_len(char **ptr);
char	**dptr_dup_replace(char **env, char *new_entry, int index);
char	**dptr_dup_add(char **env, char *new_entry);
char	*strjoin_free(char *s1, char *s2);
int		is_valid_identifier(char *str);

//builtins
void	builtins_analyzer(t_shell *shell, int flag, char **argv);

//PIPES
void	fixing_cmd_red(t_cmd *cmd, t_cmd_r *clean, t_shell *shell);
void	find_last_output_redir(t_cmd *cmd, \
	int *last_index, char **redir_type);
void	open_last_output_file(t_cmd *cmd, \
	int last_index, char *redir_type, t_shell *shell);
void	remove_last_redir_pair(t_cmd *cmd, int index);
void	remove_redir_pair(t_cmd *cmd, int index);
int		create_empty_output_file(char *type, char *filename);
int		find_input_file_index(char **content, int i);
int		find_next_double_left_index(t_cmd *cmd, int start);
int		is_redirection_token(char *s);
void	save_last_cmd(t_shell *shell, char **args);

//alocation
int		mlc_size(int j, char **mlc);
char	**dptr_dup(char	**dptr);
t_cmd_r	*alloc_clean_cmd_list(t_cmd *cmd);

//Cleaner
void	final_cleaner(t_shell *shell);
void	free_split(char **arr);
char	*special_cleaner(const char *s1, const char *s2, t_shell *shell);

//CORE
void	line_helper2(t_pipexinfo *info);
void	line_helper(t_pipexinfo *info);
void	export_print(char **argv);
void	l_comander(t_shell *shell, char *args);
void	finder_and_update(t_shell *shell);

//ECHO
void	build_echo(t_shell *shell, char **args);
void	join_expand(t_shell *data, char **result, char **str, \
		bool is_double_quote);
char	*expand_result(t_shell *data, char **line, bool is_double_quote);

//CD
void	build_cd(t_shell *shell);
void	check_cwd(void);

//PWD
void	build_pwd(t_shell *shell);
void	update_pwd(t_shell *shell);

//ENV

void	build_env(t_shell *shell);
void	update_shlvl(t_shell *shell);
char	**add_or_replace_env(char **env, char *new_entry);
int		cmp_values(char *v1, char *v2);
int		cmp_names(char *s1, char *s2);
void	update_env_var(t_shell *shell, char *arg);
void	finder_and_update(t_shell *shell);
char	*get_path_var(char *home);
char	*get_pwd_var(void);

//EXPORT
char	**build_export(t_shell *shell);
void	handle_export(t_shell *shell, t_cmd_r *clean);
char	**add_or_replace_exp(char **exp, char *new_entry);
void	update_env_export(t_shell *shell, char **args);
char	**merge_exp_lists(char **old, char **new, char **env);
int		find_in_env(char **env, const char *key);
char	*join_export(char *name, char *value);
void	update_export_var(t_shell *shell, char *arg);
int		check_duplicate_var_exist(char **env, const char *str);

//UNSET
void	build_unset(t_shell *shell, char **new_exp);
void	close_extra_fds(void);

//EXIT
void	build_exit(t_shell *shell);

//PATHS
char	*get_directory_path(char *path);
void	update_dollar_underscore(t_shell *shell);
char	*get_path(char *cmd, char **envp);

//SIGNALS
void	signal_search(t_sig_t t);
void	here_signal(int signal, siginfo_t *info, void *context);
void	root_signal(int signal, siginfo_t *info, void *context);

#endif