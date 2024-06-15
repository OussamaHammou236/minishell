#include "../header.h"


static int check_second_error_pwd(char *str)
{
    int     i;

    i = ft_strlen(str);
    if (str[0] != '-')
        return (0); // 
    else if (i == 2)
        if (str[1] == '-')
            return (2); // 2 . that mean run command without any probelm . 
    return (3); // 3 . syntax error we search for it . 
}


void    run_pwd(t_data *info, t_input temp)
{
    char *buf;
    char *p;
    int i;
    int checker_second_error = 0;

    int len_input = get_part_input(info, temp);
    if (len_input > 1)
    { 

        checker_second_error = check_second_error_pwd(temp.cmd[1]);
        if (checker_second_error == 3)
        {
            printf("minishell: pwd: %s: invalid option\n", temp.cmd[1]);
            printf("pwd: usage: pwd [-LP]\n");
            // exit status $? //
            g_exit_status = 2;
            // // ------- //

            return ;
        }   
    }
    i = 1;
    p = NULL;
    while (!p)
    {
        if (i > 1)
            free(buf);
        buf = malloc(sizeof(char) * (i * 10));
        p = getcwd(buf , i * 10);
        i++;
    }
    printf("%s\n", p);
    free(p);
    // exit status $? //
    g_exit_status = 0;
    // // ------- //

}
