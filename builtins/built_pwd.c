#include "builtin.h"

int built_pwd(void)
{
    char pwd[1024];
    if(getcwd(pwd, sizeof(pwd)))
    {
        printf("%s\n", pwd);
        return (0);
    }
    else
    {
        perror("pwd");
        return (1);
    }
}