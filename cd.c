#include "header.h"

char *get_home(t_data *info)
{
    int i = 0;

    while (info->env[i])
    {
        if (cmp_str_env(info->env[i], "HOME=", 5) == 1)
        {
            return (&info->env[i][5]);
            break ;
        }
        i++;
    }
    return (NULL);
}

void    run_cd(t_data *info, t_input temp)
{
    int len_input = get_part_input(info, temp);
    if (len_input == 1)
    {
        chdir(get_home(info));
        return ;
    }
    if (len_input == 2)
    {
        if (access(temp.cmd[1], X_OK) == 0)
        {
            chdir(temp.cmd[1]);
        }
        else
        {
            printf("cd: no such file or directory: %s\n", temp.cmd[1]);
        }
    }
}