#include "minishell.h"

void free_redirections(t_red *redir)
{
    t_red *tmp;

    while (redir)
    {
        tmp = redir->next;
        free(redir->args); 
        free(redir);      
        redir = tmp; 
    }
}

void free_cmd(t_cmd **cmds)
{
    t_cmd *tmp;
    // t_red *tmp2;
    // t_red *red;
    int i;

    if(!cmds || !*cmds)
        return ; 
    while(*cmds)
    {
        tmp = (*cmds)->next;
        i = 0;
        if((*cmds)->args)
        {
            while((*cmds)->args[i])
                free((*cmds)->args[i++]);
            free((*cmds)->args);
        }
        free_redirections((*cmds)->redirect);
        free(*cmds);
        *cmds = tmp;
    }
}


