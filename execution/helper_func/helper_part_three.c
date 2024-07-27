/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_part_three.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:43:23 by iahamdan          #+#    #+#             */
/*   Updated: 2024/07/25 14:39:22 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

char    *make_pwd()
{
    char    *p;
    char    *pwd;
    int     i;
    
    p = getcwd(NULL, 0);
    if (!p)
        return (NULL);
    pwd = malloc(sizeof(char) * (ft_strlen(p) + 5));
    pwd[0] = 'P';
    pwd[1] = 'W';
    pwd[2] = 'D';
    pwd[3] = '=';
    i = 4;
    while (i < ft_strlen(p) + 4)
    {
        pwd[i] = p[i - 4];
        i++;
    }
    pwd[i] = '\0';
    free(p);
    return (pwd);
}

char    *make_shlvl()
{
    char    *shlvl;

    shlvl = malloc(sizeof(char) * 8);
    shlvl[0] = 'S';
    shlvl[1] = 'H';
    shlvl[2] = 'L';
    shlvl[3] = 'V';
    shlvl[4] = 'L';
    shlvl[5] = '=';
    shlvl[6] = '1';
    shlvl[7] = '\0';
    return (shlvl);
}

char    *make_last()
{
    char    *last;

    last = malloc(sizeof(char) * 4);
    last[0] = '_';
    last[1] = '=';
    last[2] = ']';
    last[3] = '\0';
    return (last);
}

char    **make_mini_env()
{
    char    **new_env;
    
    new_env = malloc(sizeof(char *) * 4);
    new_env[0] = make_pwd();
    new_env[1] = make_shlvl();
    new_env[2] = make_last();
    new_env[3] = NULL;
    return (new_env);
}