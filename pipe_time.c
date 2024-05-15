#include "header.h"

void    pipe_time(t_data *info)
{
    t_input *temp;
    temp = &info->input;

   int i = 0;
    int fd[2]; // fd[0] for read  , fd[1] for write . 

    pipe(fd);
   while (i < info->number_cmd)
   {
        int id = fork();

        if (!id)
        {
            if (i == 0) // first (just write)
            {
                close(fd[0]);
                if (!check_cmd(info, temp->cmd[0]))
                {
                    // the cmd is not exist !.    
                }
                if (temp->next != NULL)
                    dup2(fd[1], 1);
                close(fd[1]);
                if (check_built_cmd(info, *temp) == 0)    
                    execve(info->current_path, temp->cmd, info->env);
            }
            else if (temp->next == NULL) // last (just read)
            {
                close(fd[1]);
                if (!check_cmd(info, temp->cmd[0]))
                {
                    // the cmd is not exist !.    
                }
                dup2(fd[0], 0);
                close(fd[0]);
                if (check_built_cmd(info, *temp) == 0)    
                    execve(info->current_path, temp->cmd, info->env);
            }
            else // bettwen first and last there is a (read & write operation) . 
            {
                if (!check_cmd(info, temp->cmd[0]))
                {
                    // the cmd is not exist !.    
                }
                dup2(fd[0], 0);
                dup2(fd[1], 1);
                close(fd[0]);
                close(fd[1]);
                if (check_built_cmd(info, *temp) == 0)    
                    execve(info->current_path, temp->cmd, info->env);
            }
        }
        else
        {
            int status;
            wait(&status);
        }
        i++;
        temp = temp->next;
   }
   //printf("pipe is done 111111111111111111111111111111111111111111\n");
}