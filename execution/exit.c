#include "../header.h"

int     is_all_numbers(char *str)
{
    int     i;

    i = 0;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (1);
        i++;
    }
    return (0);
}

void    run_exit(t_data *info, t_input temp)
{
    int len_input = get_part_input(info, temp);
    int store = 0;


    if (len_input > 1)
    {
        if (is_all_numbers(temp.cmd[1]) == 0)
        {
            if (len_input != 2)
            {
                write(2, "exit: too many arguments\n", 25);
                g_exit_status = 1;
                return ;
            }
            else
            {
                store = ft_atoi(temp.cmd[1]);
                free_something_after_exit(info);
                exit(store);
            }
        }
        else
        {
            write(2, "minishell: exit: ", 12);
            write(2, temp.cmd[1], ft_strlen(temp.cmd[1]));
            write(2,": numeric argument required\n", 28);
            free_something_after_exit(info);
            exit(2);
        }       
    }
   free_something_after_exit(info);
    exit(0);
}