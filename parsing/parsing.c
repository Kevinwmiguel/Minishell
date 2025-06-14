#include "minishell.h"

void get_redirection(t_cmd *cmd, t_token *token)
{
    t_red *red_head;
    t_red *last_red;
    t_red *redir;

    red_head = NULL;
    last_red = NULL;
  while( token && token->type != PIPE)
  {
    if(token->type == TRUNC || token->type == APPEND || token->type == INPUT || token->type == HEREDOC)
    {
        redir = malloc(sizeof(t_red));
        if(!redir)
          return ;
        redir->type = token->type;
        redir->next = NULL;
        if(token->next)
            redir->args = ft_strdup(token->next->str);
        else
            redir->args = NULL;
        if(!redir->args)
        {
            free(redir);
            return ;
        }
        if(!red_head)
            red_head = redir;
        else
            last_red->next = redir;
        last_red = redir;

        token = token->next;
    }
    token = token->next;
}
 cmd->redirect = red_head;
}

char **get_cmd(t_token *token)
{
    int count;
    int i;
    char **cmd_args;
    t_token *tmp;

    i = 0;
    count = 0;
    tmp = token;
    while(token && token->type != PIPE && token->type != INPUT && token->type != HEREDOC && token->type != TRUNC && token->type != APPEND)
    {
        if(token->type == CMD || token->type == ARG)
            count++;
        token = token->next; 
    } 
    cmd_args = malloc(sizeof(char *) * (count + 1));
    if(!cmd_args)
        return NULL;
    token = tmp;
    while(token && token->type != PIPE && token->type != INPUT && token->type != HEREDOC && token->type != TRUNC && token->type != APPEND)
    {
        if(token->type == CMD || token->type == ARG)
            cmd_args[i++] = ft_strdup(token->str);
        token = token->next; 
    }
    cmd_args[i] = NULL;
    return(cmd_args);
}

t_cmd *create_cmd(t_shell *data, t_token *token)
{
    t_cmd *cmd;
    (void)data;
    cmd = malloc(sizeof(t_cmd));
    if(cmd == NULL)
        return(NULL);
    cmd->args = get_cmd(token);
    cmd->next = NULL;
    get_redirection( cmd, token);
    return(cmd);
}

void add_cmd(t_cmd **list_cmd, t_cmd *new_cmd)
{
    t_cmd *tmp;
    if(*list_cmd == NULL)
    {
        *list_cmd = new_cmd;
        return ;
    }
    tmp = *list_cmd;
    while(tmp->next)
        tmp = tmp->next;
    tmp->next = new_cmd;
}

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
    if(!create_token_list(data, str_parse))
    {
        free(str_parse);
        return(0);
    }
    debug_tokens(data->begin);
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
                add_cmd(&lst_cmd, new_cmd);
        }
        token = token->next;
    }
    return(lst_cmd);
}

    