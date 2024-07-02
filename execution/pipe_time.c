#include "../header.h"


// hint : 
/*
exit(0) == 0
exit(1) == 256
exit(2) == 512
exit(3) == 768
exit(4) == 1024
exit(5) == 1280
*/ // those just flags .


void    printf_to_stderr(char *str)
{
    write(2, str, ft_strlen(str));
}

static void    flag_of_exit_status(void)
{
    if (g_exit_status == 1)
        exit(1);
    else if (g_exit_status == 2)
        exit(2);
    else if (g_exit_status == 125)
        exit(3);
    else if (g_exit_status == 127)
        exit(4);
    else if (g_exit_status == 130)
        exit(5);
    else
        exit(0);
}

int    pipe_time(t_data *info)
{
    t_input *temp;
    temp = &info->input;

    int fd[info->number_cmd - 1][2]; // fd[0] for read  , fd[1] for write . 
    int i = 0;
    int st;

   while (i < info->number_cmd)
   {
        if (i < info->number_cmd - 1)
            pipe(fd[i]);
        int id = fork();
        if (!id)
        {
            if (i == 0)
            { 
                // signal //
                signal(SIGINT, signal_handler_for_childs);
                // ---- //
                close(fd[i][0]);
                dup2(fd[i][1], 1);
                close(fd[i][1]);

                // -- //
                if (rediction(info, *temp) == -1)
                    flag_of_exit_status();
                // -- //
                if (!(*temp).cmd[0])
                    exit(0);
                // ------ //
                if (check_built_cmd(info, *temp) == 1)
                   flag_of_exit_status();
                if (check_cmd(info, temp->cmd[0]) == 0)
                {
                    printf_to_stderr("minishell: command not found: ");
                    printf_to_stderr(temp->cmd[0]);
                    printf_to_stderr("\n");
                    exit(4);
                }
                execve(info->current_path, temp->cmd, info->env);

            }
            else if (!temp->next)
            {
                // signal //
                signal(SIGINT, signal_handler_for_childs);
                // ---- //
                close(fd[i - 1][1]);
                dup2(fd[i - 1][0], 0);
                close(fd[i - 1][0]);
                 // -- //
                if (rediction(info, *temp) == -1)
                    flag_of_exit_status();
                // -- //
                if (!(*temp).cmd[0])
                    exit(0);
                // --//
                if (check_built_cmd(info, *temp) == 1)
                    flag_of_exit_status();
                if (check_cmd(info, temp->cmd[0]) == 0)
                {
                    printf_to_stderr("minishell: command not found: ");
                    printf_to_stderr(temp->cmd[0]);
                    printf_to_stderr("\n");
                    exit(4);
                }
                execve(info->current_path, temp->cmd, info->env);
            }
            else
            {
                // signal //
                signal(SIGINT, signal_handler_for_childs);
                // ---- //
                dup2(fd[i - 1][0], 0);
                close(fd[i -1][0]);
                dup2(fd[i][1], 1);
                close(fd[i][1]);
                // -- //
                if (rediction(info, *temp) == -1)
                    flag_of_exit_status();
                // -- //
                if (!(*temp).cmd[0])
                    exit(0);
                // --//
                 if (check_built_cmd(info, *temp) == 1)
                    flag_of_exit_status();
                if (check_cmd(info, temp->cmd[0]) == 0)
                {
                    printf_to_stderr("minishell: command not found: ");
                    printf_to_stderr(temp->cmd[0]);
                    printf_to_stderr("\n");
                    exit(4);
                }
                execve(info->current_path, temp->cmd, info->env);
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
        }
        i++;
        temp = temp->next;
   }
   while(waitpid(-1, &st, 0) != -1)
   {
        if (st == 0)
            g_exit_status = 0;
        else if (st == 256)
            g_exit_status = 1;
        else if (st == 512)
            g_exit_status = 2;
        else if (st == 768)
            g_exit_status = 125;
        else if (st == 1024)
            g_exit_status = 127;
        else if (st == 1280 || st == 2)
            return (g_exit_status = 130, 0);
   }
   
    return (0);
}
