#include "minishell.h"

bool is_space(char c)
{
    if( c && (c >= 9 && c <= 13 ) || c == ' ')
        return(true);
    return(false);
}
void skip_space(char **line)
{
    char *str;
    str = *line;
    while(is_space(*str))
        str++;
    *line = str;
}

bool special_char( char *str)
{
    if(str && ft_strlen(str) >= 2)
    {
        if(ft_strncmp(str, "<<", 2) == 0)
            return(true);
        else if(ft_strncmp(str, ">>", 2) == 0)
            return(true);
    }
    if(str && ft_strlen(str) >= 1)
    {
        if(ft_strncmp(str, "<", 1) == 0)
            return(true);
        else if (ft_strncmp(str, ">", 1) == 0)
            return (true);
        else if (ft_strncmp(str, "|", 1) == 0)
            return (true);
    }
    return(false);
}

char *get_special_char(char **str)
{
    char *s_char;
    s_char = NULL;
    if(ft_strncmp(*str, "<<", 2) == 0)
        s_char = ft_strdup("<<");
    else if(ft_strncmp(*str, ">>", 2) == 0)
        s_char = ft_strdup(">>");
    else if (ft_strncmp(*str, "<", 1)==0)
        s_char = ft_strdup("<");
    else if(ft_strncmp(*str, ">", 1) == 0)
        s_char = ft_strdup(">");
    else if(ft_strncmp(*str, "|", 1) == 0)
        s_char = ft_strdup("|");
    *str = (*str) + ft_strlen(s_char);
    return(s_char);
}