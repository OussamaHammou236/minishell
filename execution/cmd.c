#include "../header.h"

void	handler_ctrl_backslash_child(int x)
{
    // do nothing
}

void    run_cmd(t_data *info, char **cmd)
{
    int pid = fork();
    int s;

    g_exit_status = 0;
    signal(SIGQUIT, handler_ctrl_backslash_child);
    if (!pid)
    {
        execve(info->current_path, cmd, info->env);
    }
    else
    {
        wait(&s);
        signal(SIGQUIT, handler_ctrl_backslash);
        if (g_exit_status == 130)
            return ;
        g_exit_status = get_exit_status(s);
    }
}