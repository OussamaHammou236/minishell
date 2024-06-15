#include "../header.h"

int     check_equality(char *str1_env , char *variable)
{
    int     i;

    i = 0;
    while (str1_env[i] != '=')
    {
        if (str1_env[i] != variable[i])
            return (-1);
        i++;
    }
    if (variable[i])
        return (-1);
    return (1);
}

int    check_var_exist(t_data *info, char *str)
{
    int     i;

    i = 0;
    while (info->env[i])
    {
        if (check_equality(info->env[i], str) == 1)
            return (i);
        i++;
    }
    return (-1);
}

void    delete_var_from_env(t_data *info, int posi)
{
    int     i;
    int     j;
    int     len;
    char    **upd_env;

    i = 0;
    j = 0;
    len = 0;
    while (info->env[len])
        len++;
    upd_env = malloc(sizeof(char *) * len);
    while (info->env[i])
    {
        if (i != posi)
            upd_env[j] = ft_strdup(info->env[i]);
        i++;
        if (i != posi)
            j++;
    }
    upd_env[j] = NULL;
    ft_free_env(info, len);
    info->env = upd_env;
}

static int check_second_error_unset(char *str)
{
    int     i;

    i = ft_strlen(str);
    if (str[0] != '-')
        return (0); // 
    else if (i == 2)
        if (str[1] == '-')
            return (2); // 2 . that mean run command without any probelm . 
    return (3); // 3 . syntax error we search for it . 
}


void    run_unset(t_data *info, t_input temp)
{
    int len_input = get_part_input(info, temp);
    int i = 1;
    int posi = 0;
    int checker_second_error = 0;

    if (len_input == 1)
        return ;
    else
    {
        // check error //
        checker_second_error = check_second_error_unset(temp.cmd[1]);
        if (checker_second_error == 3)
        {
            printf("minishell: unset: %s: invalid option\n", temp.cmd[1]);
            printf("unset: usage: unset [-f] [-v] [-n] [name ...]\n");
            // exit status $? //
            g_exit_status = 2;
            // ------- //

            return ;
        }
         // ------ //
        while (temp.cmd[i])
        {
            posi = check_var_exist(info, temp.cmd[i]);
            if (posi != -1)
                delete_var_from_env(info, posi);
            i++;
        }
    }
    // exit status $? //
    g_exit_status = 0;
    // // ------- //

}