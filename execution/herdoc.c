#include "../header.h"

void     print_error_permi(char *str, t_data *info)
{
    write(2, "minishell: ", 11);
    write(2, str, ft_strlen(str));
    write(2, ": Permission denied", 19);
    write(2, "\n", 1);

    // exit status $? //
    g_exit_status = 1;
    // // ------- //

}


int    rediction(t_data *info, t_input temp)
{
    int     i;
    int     posi;
    int     our_fd_in;
    int     our_fd_out;
    char    *str;
    int     status;
    int     error_file;
    int     posi_error_file;
    int fd[2];
    posi = -1;
    i = 0;
    error_file = 0;
    posi_error_file = -1;
    our_fd_in = -1;
    our_fd_out = -1;
    status = 0; // 1 mean < and 2 mean << .

    // --   -- //

    // ------------ //
    while (temp.red[i])
    {
        if (cmp_str(temp.red[i], ">") == 1)
        {
            posi = i;
            if (error_file != 1)
            {
                our_fd_in = open(temp.red[posi + 1], O_CREAT | O_RDWR, 0644);
                if(access(temp.red[posi + 1] , W_OK) == -1) 
                    return (print_error_permi(temp.red[posi + 1], info), -1);
            }
        }
        else if (cmp_str(temp.red[i], ">>") == 1)
        {
            posi = i;
            if (error_file != 1)
            {
                our_fd_in = open(temp.red[posi + 1], O_APPEND | O_RDWR | O_CREAT, 0644);
                if(access(temp.red[posi + 1] , W_OK) == -1) 
                    return (print_error_permi(temp.red[posi + 1], info), -1);
            }
        }
        else if (cmp_str(temp.red[i], "<") == 1)
        {
            posi = i;
            if(access(temp.red[posi + 1] , F_OK) != 0) 
            {
                if (error_file != 1)
                    posi_error_file = posi + 1;
                error_file = 1;
            }
            else
            {
                if(access(temp.red[posi + 1] , R_OK) == -1) 
                    return (print_error_permi(temp.red[posi + 1], info), -1);
                our_fd_out = open(temp.red[posi + 1],  O_RDONLY , 0644);
                status = 1;
            }
        }
        else if (cmp_str(temp.red[i], "<<") == 1)
        {
            
            pipe(fd);
            posi = i;
            int id = fork();
            if (!id)
            {
                // signal //
                signal(SIGINT, signal_handler_for_childs);
                // ---- //
                close(fd[0]);
                // -solver problem of stdin stdout- //
                dup2(info->flags.fd_stdin, 0);
                dup2(info->flags.fd_stdout, 1);
                // -- //
                while (1)
                {
                    str = readline("> ");
                    if (cmp_str(str, temp.red[posi + 1]) == 1)
                    {
                        free(str);
                        break ;
                    }
                    write(fd[1], str, strlen(str));
                    write(fd[1], "\n", 1);
                    free(str);
                }
                close(fd[1]);
                exit(0);
            }
            else
            {
                close(fd[1]);
                int st;
                wait(&st);
                if (st == 1280) // that mean the child was exit by signal SIGINT.
                {
                    return (-1);
                }
                // --- //
                status = 2;
                // --- //
                // close(fd[0]);
            }
        }
        i++;
    }
    if (posi == -1)
        return 0;
    else
    {
        if (error_file == 1)
        {
            printf("minishell: %s: No such file or directory\n", temp.red[posi_error_file]);
                // exit status $? //
                g_exit_status = 1;
                // // ------- //

            return (-1);
        }
        if (status == 1)
        {
            dup2(our_fd_out, 0);
            info->flags.dup_stdin_used = 1;
        }
        else if (status == 2)
        {
            dup2(fd[0], 0);
            close(fd[0]);
            info->flags.dup_stdin_used = 1;
        }
        if (our_fd_in != -1)
        {
            dup2(our_fd_in, 1);
            close(our_fd_in);
            info->flags.dup_stdout_used = 1;
        }
    }
    return 0;
}