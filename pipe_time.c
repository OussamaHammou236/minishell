#include "header.h"

int    pipe_time(t_data *info)
{
    t_input *temp;
    temp = &info->input;


    int fd[info->number_cmd - 1][2]; // fd[0] for read  , fd[1] for write . 
    int i = 0;
   while (i < info->number_cmd)
   {
        if (i < info->number_cmd - 1)
            pipe(fd[i]);
        int id = fork();
        if (!id)
        {
            if (i == 0)
            { 
                if (check_cmd(info, temp->cmd[0]) == 0)
                {
                    printf("minishell: command not found: %s\n", temp->cmd[0]);
                    return (0);
                }
                close(fd[i][0]);
                dup2(fd[i][1], 1);
                close(fd[i][1]);
                if (check_built_cmd(info, *temp) == 0)
                    execve(info->current_path, temp->cmd, info->env);
                else
                    exit(0);
            }
            else if (!temp->next)
            {
                if (check_cmd(info, temp->cmd[0]) == 0)
                {
                    printf("minishell: command not found: %s\n", temp->cmd[0]);
                    return (0);
                }
                close(fd[i - 1][1]);
                dup2(fd[i - 1][0], 0);
                close(fd[i - 1][0]);
                if (check_built_cmd(info, *temp) == 0)
                    execve(info->current_path, temp->cmd, info->env);
                else
                    exit(0);
            }
            else
            {
                if (check_cmd(info, temp->cmd[0]) == 0)
                {
                    printf("minishell: command not found: %s\n", temp->cmd[0]);
                    return (0);
                }
                dup2(fd[i - 1][0], 0);
                close(fd[i -1][0]);
                dup2(fd[i][1], 1);
                close(fd[i][1]);
                if (check_built_cmd(info, *temp) == 0)
                    execve(info->current_path, temp->cmd, info->env);
                else
                    exit(0);
            }
        }
        else
        {
            if (i == 0)
                close(fd[i][1]);
            else if (!temp->next)
                close(fd[i -1][0]);
            else
            {
                close(fd[i - 1][0]);
                close(fd[i][1]);
            }
            int st;
            wait(&st);
        }
        i++;
        temp = temp->next;
   }
    return (0);
}
