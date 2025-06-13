#include "minishell.h"

int process_shell_input(t_shell *data, char *str)
{
    char *str_parse;
    if(ft_strlen(str) == 0)
        return(0);
    if(verify_closed_quote(str))
    {
        printf("Error: Unclosed quote.\n");
        fflush(stdout);
        return(0);
    }
    str_parse = expand_str(data, str);
    if(str_parse == NULL)
        return(0);
    if(!create_tokenlist(data, str_parse))
    {
        free(str_parse);
        return(0);
    }
    free(str_parse);
    return(1);
}

t_cmd *parse_cmd(t_shell *data, t_token *token)
{
    t_cmd *lst_cmd;
    t_cmd   *new_cmd;

    lst_cmd = NULL;
    while(token)
    {
        if(!token->prev || token->prev->type == PIPE)
        {
            new_cmd = create_cmd(data, token);
            if(!new_cmd)
            {
                free_cmd(&new_cmd);
                free_cmd(&lst_cmd);
                return(NULL);
            }
            if (!lst_cmd)
                lst_cmd = new_cmd;
            else   
                add_cmd(lst_cmd, new_cmd);
        }
        token = token->next;
    }
    return(lst_cmd);
}

    