#include "minishell.h"

bool is_builtin(char *cmd)
{
	if (!cmd)
		return false;
	return (
		strcmp(cmd, "pwd") == 0 ||
		strcmp(cmd, "cd") == 0 ||
		strcmp(cmd, "env") == 0
	);
}

int exec_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (strcmp(cmd->args[0], "pwd") == 0)
		return built_pwd();
	else if (strcmp(cmd->args[0], "cd") == 0)
	    return built_cd(cmd->args);
	else if (strcmp(cmd->args[0], "env") == 0)
	    return built_env(shell->env);
	return (1);
}
