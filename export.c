#include "header.h"

int     check_correct_arg(char *str) // -1 for error , 1 for correct , 0 for skip.
{
    int i = 0;

   
    if (str[i] >= '0' && str[i] <= '9')
        return (-1);
    while (str[i] && str[i] != '=')
        i++;
    if (i == 0)
        return (-1);
    if (!str[i])
        return (0);
    return (1);
}

void    add_var_to_env(t_data *info, char *variable)
{
    int     i;
    int     len;
    char    **upd_env;

    i = 0;
    len = 0;
    while (info->env[len])
        len++;
    upd_env = malloc(sizeof(char *) * (len + 2));
    while (info->env[i])
    {
        upd_env[i] = ft_strdup(info->env[i]);
        if (len > 2)
        {
            if (!info->env[i + 2])
                break ;
        }
        i++;
    }
    upd_env[++i] = ft_strdup(variable);
    upd_env[i + 1] = ft_strdup(info->env[i]);
    upd_env[i + 2] = NULL;
    ft_free_env(info, len);
    info->env = upd_env;
}

void    display_exporting_var(t_data *info)
{
    int     i;
    int     j;
    int     flag;

    flag = 0;
    j = 0;
    i = 0;
    while (info->env[i + 1])
    {
        j = 0;
        flag = 0;
        printf("declare -x ");
        while (info->env[i][j])
        {
            printf("%c", info->env[i][j]);
            if (flag == 0 && info->env[i][j] == '=')
            {
                printf("\"");
                flag = 1;
            }
            j++;
        }
        printf("\"\n");
        i++;
    }
}

void    run_export(t_data *info, t_input temp)
{
    int len_input = get_part_input(info, temp);
    int     i;
    int checker;

    i = 1;
    checker = 0;
    if (len_input == 1)
        display_exporting_var(info);
    else
    {
        while (temp.cmd[i])
        {
            checker = check_correct_arg(temp.cmd[i]);
            if (checker == -1)
                printf("minishell: export: '%s': not a valid identifier\n", temp.cmd[i]);
            else if (checker == 0)
            {
                i++;
                continue;
            }
            else
                add_var_to_env(info, temp.cmd[i]);
            i++;
        }
    }

}