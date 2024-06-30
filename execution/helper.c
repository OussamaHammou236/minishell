#include "../header.h"

int get_len_number(int x)
{
    int i = 0;
    int store = 0;

    if (x == 0)
        return (1);
    store = x / 10;
    while (store != 0)
    {
        store = store / 10;
        i++;
    }
    i++;
    return (i);
}
char    *make_new_shlvl(t_data *info, int posi)
{
    int i;
    int my_num = 0;
    char *my_num_in_str;
    int len = 0;
    char    *new_shlvl;

    i = 0;

    while (info->env[posi][i] != '=')
        i++;
    i++;
    my_num = ft_atoi(&info->env[posi][i]);
    my_num++;
    my_num_in_str = ft_itoa(my_num);
    len = 6 + get_len_number(my_num);  
    new_shlvl = malloc(sizeof(char) * len + 1);
    i = 0;
    while (info->env[posi][i] != '=')
    {
        new_shlvl[i] = info->env[posi][i];
        i++;
    }
    new_shlvl[i] = info->env[posi][i];
    i++;
    while (my_num_in_str[i - 6])
    {
        new_shlvl[i] = my_num_in_str[i - 6];
        i++;
    }
    new_shlvl[i] = '\0';
    return (new_shlvl);
}

void    shlvl_increament(t_data *info)
{
    int     i;
    char *new_shlvl;

    i = 0;
    while (info->env[i])
    {
        if (cmp_str_env(info->env[i], "SHLVL=", 6) == 1)
        {
            new_shlvl = make_new_shlvl(info, i);
            free(info->env[i]);
            info->env[i] = new_shlvl;
            return ;
        }
        i++;
    }
}

void    initialization(t_data *info)
{
    info->flags.is_builtin_cmd = 0;
    info->number_cmd = 0;

    info->flags.fd_stdout = dup(1);
    info->flags.fd_stdin = dup(0);
    info->flags.dup_stdin_used = 0;
    info->flags.dup_stdout_used = 0;

    shlvl_increament(info);

}

int     cmp_str_env(char *str1, const char *str2, int len_str2)
{
    int i = 0;

    while (i < len_str2 && str1[i])
    {
        if (str1[i] != str2[i])
            return (0);
        i++;
    }
    if (str1[i] == '\0' && i != len_str2)
        return (0);
    return (1);
}


int get_part_input(t_data *info, t_input temp)
{
    int i = 0;
    while (temp.cmd[i])
    {
        i++;
    }
    return (i);
}

void    extract_path(char **env, t_data *info)
{
    int i = 0;
    while (env[i])
    {
        if (cmp_str_env(env[i], "PATH=", 5) == 1)
        {
            info->path = ft_split(&env[i][5], ':');
            break ;
        }
        i++;
    }
}



int cmp_str(char *str1, char *str2)
{
    int i = 0;
    
    if (!str1 || !str2)
        return (0);
    while (str1[i] || str2[i])
    {
        if (str1[i] != str2[i])
            return (0);
        i++;
    }
    return (1);
}

char    **duplacte_env(char **env)
{
    int     i;
    char    **our_env;

    i = 0;
    while (env[i])
        i++;
    our_env = malloc(sizeof(char*) * (i + 1));
    i = 0;
    while (env[i])
    {
        our_env[i] = ft_strdup(env[i]);
        i++;
    }
    our_env[i] = NULL;
    return (our_env);
}


