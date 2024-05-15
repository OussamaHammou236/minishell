#include "header.h"

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

void    run_unset(t_data *info, t_input temp)
{
    int len_input = get_part_input(info, temp);
    int i = 1;
    int posi = 0;

    if (len_input == 1)
        return ;
    else
    {
        while (temp.cmd[i])
        {
            posi = check_var_exist(info, temp.cmd[i]);
            if (posi != -1)
                delete_var_from_env(info, posi);
            i++;
        }
    }
}