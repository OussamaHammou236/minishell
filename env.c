#include "header.h"

void    run_env(t_data *info, t_input temp)
{
    int len_input = get_part_input(info, temp);
    int i = 0;
    if (len_input > 1)
    {
       printf("error in number of arg \n");
       return ;
    }
    while (info->env[i])
    {
        printf("%s\n", info->env[i]);
        i++;
    }
}