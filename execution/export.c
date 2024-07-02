#include "../header.h"

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
        if (flag == 1)
            printf("\"");
        printf("\n");
        i++;
    }
}

int check_second_error_export(char *str)
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

int     check_correct_arg(char *str, int *sign_plus) 
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

    return (1);
}

static int    check_equality(char *var_env, char *user_var)
{
    int     i;

    i = 0;
    
    while (var_env[i] != '\0' && var_env[i] != '=')
    {
        if (var_env[i] != user_var[i])
            return (1);
        i++;
    }
    if (var_env[i] == '=' && user_var[i] != '\0')
    {
        if (var_env[i] != user_var[i])
            return (1); 
    }
    else if (user_var[i] != '\0' && user_var[i] != '=')
        return (1);
    return (0);
}

int check_is_exist(char **env, char *user_var)
{ 
    int     i;

    i = 0;
    while (env[i])
    {
        if (check_equality(env[i], user_var) == 0)
            return (i);
        i++;
    }
    return (-1);
}

int     is_containe_equal_flag(char *user_var)
{
    int     i;

    i = 0;
    while (user_var[i])
    {
        if (user_var[i] == '=')
            return (0);
        i++;
    }
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
    int var_not_containes_equal;

    var_not_containes_equal = 0;
    while (variable[i] != '=')
        i++;
    i++;
    while (variable[i])
    {
        i++;
        len_var++;
    }
    // --- handle = -- //
    if (is_containe_equal_flag(info->env[posi]) == 1)
        var_not_containes_equal = 1;
    // -- //
    len_total = len_var + ft_strlen(info->env[posi]) + 1 + var_not_containes_equal;
    new_variable = malloc(sizeof(char) * len_total);
    i = 0;

    var = ft_strlen(variable) - len_var;
    while (i < len_total)
    {
        if (info->env[posi][i])
            new_variable[i] = info->env[posi][i];
        else
        {
            if (var_not_containes_equal == 1)
            {
                new_variable[i] = '=';
                i++;
            }
            break;
        }
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
        if (check_equality(info->env[i], new_var) == 0)
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


void    add_var_to_env(t_data *info, char *variable , int sign_plus)
{
    int     i;
    int     len;
    char    **upd_env;
    int     checker;

    checker = 0;
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


void    export_operation(t_data *info, char *user_var, int sign_plus)
{
    int     check_existance;


    // first of all , we need to check if that variable already exist in the env . 
    check_existance = check_is_exist(info->env, user_var);

    if (check_existance != -1)
    {
        if (is_containe_equal_flag(user_var) == 1)
            return ;
        else
        {
            free(info->env[check_existance]);
            info->env[check_existance] = ft_strdup(user_var);
            return ;
        }
    }
    else
        add_var_to_env(info, user_var, sign_plus);
}


void    run_export(t_data *info, t_input temp)
{
    int len_input = get_part_input(info, temp);
    int     i;
    int checker;
    int checker_second_error = 0;
    int sign_plus;
    int error_occurs;

    error_occurs = 0;
    sign_plus = 0;
    i = 1;
    checker = 0;
    if (len_input == 1)
        display_exporting_var(info);
    else
    {
        checker_second_error = check_second_error_export(temp.cmd[1]);
        if (checker_second_error == 2)
        {
            display_exporting_var(info);
            g_exit_status = 0;
            return ;
        }
        else if (checker_second_error == 3)
        {
            printf("minishell: export: %s: invalid option\n", temp.cmd[1]);
            printf("export: usage: export [-fn] [name[=value] ...] or export -p\n");
            g_exit_status = 2;
            return ;
        }
        //-----------------//
        while (temp.cmd[i])
        {
           checker = check_correct_arg(temp.cmd[i], &sign_plus);
            if (checker == -1)
            {
                printf("minishell: export: '%s': not a valid identifier\n", temp.cmd[i]);
                g_exit_status = 1;
                error_occurs = 1;
            }
            else
                export_operation(info, temp.cmd[i], sign_plus);
            i++;
        }
    }
    if (error_occurs == 0)
        g_exit_status = 0;
}