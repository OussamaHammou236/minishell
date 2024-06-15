#include "../header.h"

char *get_current_path(void)
{
    char *p;
    char *buf;
    int     i;

    i = 1;
    p = NULL;
    while (!p)
    {
        if (i > 1)
            free(buf);
        buf = malloc(sizeof(char) * (i * 10));
        p = getcwd(buf , i * 10);
        i++;
    }
    return (p);
}

char *make_format_path(char *str)
{
    int     i;
    int     len;
    char       *new_path;

    len = ft_strlen(str);
    new_path = malloc(sizeof(char) * (len  + 5)); // 4 or 5 ? i dont know . (for null terminator).
    new_path[0] = 'P';
    new_path[1] = 'W';
    new_path[2] = 'D';
    new_path[3] = '=';
    i = 4;
    while (i < len + 4)
    {
        new_path[i] = str[i - 4];
        i++;
    }
    new_path[i] = '\0';
    return (new_path);
}

void    update_old_pwd(t_data *info, char *str)
{
    int     i;
    int     len;
    char       *new_path;

    len = ft_strlen(str);
    new_path = malloc(sizeof(char) * (len  + 4)); // 4 or 3 ? i dont know . (for null terminator).
    new_path[0] = 'O';
    new_path[1] = 'L';
    new_path[2] = 'D';
    i = 3;
    while (i < len + 3)
    {
        new_path[i] = str[i - 3];
        i++;
    }
    new_path[i] = '\0';
    // part 2 //
    i = 0;
    while (info->env[i])
    {
        if (cmp_str_env(info->env[i], "OLDPWD=", 7) == 1)
        {
            free(info->env[i]);
            info->env[i] = new_path;
            break ;
        }
        i++;
    }

}

void    update_env(t_data *info)
{
    char *new_path = get_current_path();

    int i = 0;
    while (info->env[i])
    {
        if (cmp_str_env(info->env[i], "PWD=", 4) == 1)
        {
            update_old_pwd(info, info->env[i]);
            free(info->env[i]);
            info->env[i] = make_format_path(new_path);
            free(new_path);
            break ;
        }
        i++;
    }
}



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

static int check_second_error_cd(char *str)
{
    int     i;

    i = ft_strlen(str);
    if (str[0] != '-')
        return (0); //.
    
    if (i == 2)
        if (str[1] == '-')
            return (2); // 2 . that mean run command without any probelm . 
    return (3); // 3 . syntax error we search for it . 
}


void    run_cd(t_data *info, t_input temp)
{
    int len_input = get_part_input(info, temp);
    int checker_second_error = 0;

    if (len_input == 1)
    {
        chdir(get_home(info));
        // // exit status $? //
        g_exit_status = 0;
        // // ------- //
        return ;
    }
    if (len_input == 2)
    {

         // error of "-" . 
        checker_second_error = check_second_error_cd(temp.cmd[1]);

        if (checker_second_error == 2)
        {
             chdir(get_home(info));
            // // exit status $? //
            g_exit_status = 0;
            // // ------- //
             return ;
        }
        else if (checker_second_error == 3)
        {
            printf("minishell: cd: %s: invalid option\n", temp.cmd[1]);
            printf("cd: usage: cd [-L|[-P [-e]] [-@]] [dir]\n");
            // // exit status $? //
            g_exit_status = 2;
            // // ------- //
            return ;
        }   
    

        // ---------- ///

        if (access(temp.cmd[1], X_OK) == 0)
        {
            chdir(temp.cmd[1]);
            // exit status $? //
            g_exit_status = 0;
            // ------- //
            
        }
        else
        {
            printf("cd: no such file or directory: %s\n", temp.cmd[1]);
            // // exit status $? //
            g_exit_status = 1;
            // // ------- //
        }
    }
    else
    {
        printf("minishell: cd: too many arguments\n");
        // // exit status $? //
            g_exit_status = 1;
        // // ------- //
    }
    
}