#include "header.h"

void    run_pwd(t_data *info, t_input temp)
{
    char *buf;
    char *p;
    int i;

    int len_input = get_part_input(info, temp);
    if (len_input > 1)
    {
        // wrong argument . !
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
}
