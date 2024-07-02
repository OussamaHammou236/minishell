#include "../header.h"


static int check_second_error_env(char *str)
{
    int     i;

    i = ft_strlen(str);
    if (str[0] != '-')
        return (0); // syntax error with no "-" .
    if (i == 1)
        return (1); // 1 . that mean dont do nothing . 
    else if (i == 2)
        if (str[1] == '-')
            return (2); // 2 . that mean run command without any probelm . 
    return (3); // 3 . syntax error we search for it . 
}

void    run_env(t_data *info, t_input temp)
{
    int len_input = get_part_input(info, temp);
    int i = 0;
    int check_error = 0;

    if (len_input > 1)
    {
        check_error = check_second_error_env(temp.cmd[1]);

        if (check_error == 0)
        {
            printf("env: '%s': No such file or directory\n", temp.cmd[1]);
            // // exit status $? //
            g_exit_status = 127;
            // // ------- //
            return ;
        }
        else if (check_error == 1)
        {
            // // exit status $? //
            g_exit_status = 0;
            // // ------- //
            return ;
        }
        else if (check_error == 3)
        {
            printf("env: invalid option -- '%s'\n", temp.cmd[1]);
            printf("Try 'env --help' for more information.\n");
            // // exit status $? //
            g_exit_status = 125;
            // // ------- //
            return ;
        }
    }
    // -display last cmd- //

    // ------ //
    while (info->env[i])
    {
        if (!info->env[i + 1])
        {
            printf("_=/usr/bin/env\n");
            break;
        }
        if (is_containe_equal_flag(info->env[i]) == 0)
            printf("%s\n", info->env[i]);
        i++;
    }
    // // exit status $? //
    g_exit_status = 0;
    // // ------- //
}
