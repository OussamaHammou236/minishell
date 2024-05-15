#include "header.h"

void    initialization(t_data *info)
{
    info->flags.is_builtin_cmd = 0;
    info->number_cmd = 0;

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


