#include "minishell.h"

void handle_sigint(int code)
{
    (void)code;
    if(g_signal.heredoc)
        return ;
    write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    if(g_signal.pid== 0)
        rl_redisplay();
}
void handle_sigsegv(int code)
{
    (void)code;
    write(1, "Segmentation fault\n", 19);
}

void handle_sigabrt(int code)
{
    (void)code;
    write(1, "abort\n", 6);
}