#include "header.h"

void    ft_free_env(t_data *info, int len)
{
    int     i;

    i = 0;
    while (i < len)
    {
        free(info->env[i]);
        i++;
    }
    free(info->env);
}
