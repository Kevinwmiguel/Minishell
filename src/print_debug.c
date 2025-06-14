#include "minishell.h"


void debug_tokens(t_token *token)
{
    while (token)
    {
        printf("Token: %-10s | Type: %d\n", token->str, token->type);
        token = token->next;
    }
}

void print_redirects(t_red *red)
{
    while (red)
    {
        printf("  Redirect type: %d\n", red->type);
        printf("  Redirect args: %s\n", red->args);
        red = red->next;
    }
}

void print_cmd(t_cmd *cmd)
{
	if (!cmd) return;
	printf("======================\n");
	int i = 0;
	while (cmd->args[i])
		printf("%s\n", cmd->args[i++]);
	if(cmd->redirect)
	{
		printf("Redirections:\n");
		print_redirects(cmd->redirect);
	}
	else
		printf("NO redirection\n");
	print_cmd(cmd->next);
}

