#include "../header.h"

void    run_echo(t_data *info, t_input temp)
{
    int len_input = get_part_input(info, temp);
    int     i = 1;
    if (len_input == 1)
    {
        printf("\n");
    }
    else
    {
        if (cmp_str(temp.cmd[1], "-n") == 1)
            i++;
        while (temp.cmd[i])
        {
            printf("%s", temp.cmd[i]);
            if (temp.cmd[i + 1])
                printf(" ");
            i++;
        }
        if (cmp_str(temp.cmd[1], "-n") != 1)
            printf("\n");
    }
    // // exit status $? //
    g_exit_status = 0;
    // // ------- //
}