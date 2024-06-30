#include "../header.h"

int     check_correct_arg(char *str, int *sign_plus) // -1 for error , 1 for correct , 0 for skip. // 2 for correct , += . 
{
    int i = 0;
   
    if (str[i] >= '0' && str[i] <= '9')
        return (-1);
    while (str[i] && str[i] != '=')
    {
        if (str[i + 1] == '=')
        {
            if (str[i] == '+')
                *sign_plus = 1;
        }
        if (*sign_plus == 0)
        {
            if ((str[i] < 'a' || str[i] > 'z') 
                && (str[i] < 'A' || str[i] > 'Z') 
                && (str[i] < '0' || str[i] > '9'))
                    return (-1);
        }
        i++;
    }
    if (i == 0)
        return (-1);
    if (!str[i])
        return (0);
    return (1);
}

int len_str_equal(char *str)
{
    int i = 0;

    while (str[i] != '=')
    {
        i++;
    }
    return (i + 1);
}

void    upd_variable(t_data *info, char *variable, int posi)
{
    char *new_variable;

    int len_var = 0;
    int i = 0;
    int len_total;
    int var;
    while (variable[i] != '=')
        i++;
    i++;
    while (variable[i])
    {
        i++;
        len_var++;
    }
    len_total = len_var + ft_strlen(info->env[posi]) + 1;
    new_variable = malloc(sizeof(char) * len_total);
    i = 0;

    var = ft_strlen(variable) - len_var;
    while (i < len_total)
    {
        if (info->env[posi][i])
            new_variable[i] = info->env[posi][i];
        else
            break;
        i++;
    }
    while (i < len_total)
    {
        if (variable[var])
        {
            new_variable[i] = variable[var];
            var++;
        }
        else
            new_variable[i] = '\0';
        i++;
    }



    free(info->env[posi]);
    info->env[posi] = new_variable;
}

int    handle_sign_plus(t_data *info, char *variable) // export += . 
{
    char *new_var;
    int i = 0;
    int j = 0;
    int len = len_str_equal(variable);

    new_var = malloc(sizeof(char) * len);
    while (i < len - 1)
    {
        if (variable[i] == '+')
            j++;
        new_var[i] = variable[j];
        i++;
        j++;
    }
    new_var[len - 1] = '\0';
    i = 0;
    while (info->env[i])
    {
        if (cmp_str_env(info->env[i], new_var, ft_strlen(new_var)) == 1)
        {
            upd_variable(info, variable, i);
            free(new_var);
            return 0;
        }
        i++;
    }
    free(new_var);
    return (1);
}

char    *ft_strdup_export(char *variable)
{
    int len = ft_strlen(variable);
    char *new_var = malloc(len);

    int i = 0;
    int j = 0;
    while (i < len)
    {
        if (variable[i] == '+')
            j++;
        new_var[i] = variable[j];
        i++;
        j++;
    }   
    return (new_var);
}

void    add_var_to_env(t_data *info, char *variable , int sign_plus)
{
    int     i;
    int     len;
    char    **upd_env;

    i = 0;
    len = 0;

    if (sign_plus == 1)
    {
        if (handle_sign_plus(info, variable) == 0)
            return ;
    }

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
    if (sign_plus == 1)
        upd_env[++i] = ft_strdup_export(variable);
    else    
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

static int check_second_error_export(char *str)
{
    int     i;

    i = ft_strlen(str);
    if (str[0] != '-')
        return (0); // .
   
    if (i == 2)
        if (str[1] == '-')
            return (2); // 2 . that mean run command without any probelm . 
    return (3); // 3 . syntax error we search for it . 
}



void    run_export(t_data *info, t_input temp)
{
    int len_input = get_part_input(info, temp);
    int     i;
    int checker;
    int checker_second_error = 0;
    int sign_plus;

    sign_plus = 0;
    i = 1;
    checker = 0;
    if (len_input == 1)
        display_exporting_var(info);
    else
    {
        // error of "-" . 
        checker_second_error = check_second_error_export(temp.cmd[1]);
        if (checker_second_error == 2)
        {
            display_exporting_var(info);
            // exit status $? //
            g_exit_status = 0;
             // // ------- //
            return ;
        }
        if (checker_second_error == 3)
        {
            printf("minishell: export: %s: invalid option\n", temp.cmd[1]);
            printf("export: usage: export [-fn] [name[=value] ...] or export -p\n");
            // exit status $? //
            g_exit_status = 2;
            // ------- //

            return ;
        }   


        // ---------- ///


        while (temp.cmd[i])
        {
            checker = check_correct_arg(temp.cmd[i], &sign_plus);
            
            if (checker == -1)
            {
                printf("minishell: export: '%s': not a valid identifier\n", temp.cmd[i]);
                // exit status $? //
                g_exit_status = 1;
                // ------- //
                return ;
            }
            else if (checker == 0)
            {
                i++;
                continue;
            }
            else
                add_var_to_env(info, temp.cmd[i], sign_plus);
            i++;
        }
    }
    // exit status $? //
    g_exit_status = 0;
    // // ------- //


}