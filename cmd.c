#include "header.h"

void    run_cmd(t_data *info, char **cmd)
{
    int pid = fork();
    int s;

    if (!pid)
        execve(info->current_path, cmd, info->env);
    else
    {
        wait(&s);
    }
}