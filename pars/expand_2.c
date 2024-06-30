/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:44:35 by ohammou-          #+#    #+#             */
/*   Updated: 2024/06/30 18:49:26 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char *ft_malloc(char *str, int len, t_trash **trash)
{
    str = malloc(len);
    ft_bzero(str, len);
    add_to_trash(str,trash);
    return str;
}

char *add_qoutes(char *str, t_trash **trash)
{
	t_data data;
    data.i = 0;
    data.j = 1;
    data.len = ft_strlen(str) + (cont_words(str,' ') * 2);
    data.str = malloc(data.len + 1);
    ft_bzero(data.str, data.len + 1);
    data.str[0] = '"';
    while(str[data.i])
    {
        if(str[data.i] != ' ' && str[data.i + 1] == ' ')
        {
            data.str[data.j] = str[data.i];
            data.str[++data.j] = '"';
            data.str[++data.j] = ' ';
        }
        else if (str[data.i] == ' ' && str[data.i + 1] != ' ')
            data.str[data.j] = '"';
        else
            data.str[data.j] = str[data.i];
        data.i++;
        data.j++;
    }
    data.str[data.j] = '"';
    free(str);
    return data.str;
}
// "ls  > out
char *expand_str(char *str, t_trash **trash, t_data *info, int fg)
{
	t_data data;	
	data.flag = DOUBLE_Q_OFF;
	data.flag1 = SINGLE_Q_OFF;
    data.j  = ft_strlen(str) + 1;
    data.str = ft_malloc(data.str, data.j, trash);
    data.len = 0;
    data.i = 0;

    while (str[data.i])
    {
        double_single_Q(&data,str[data.i]);
        if (str[data.i] == '$' && (str[data.i + 1] == '"' || str[data.i + 1] == '\'') && data.flag == DOUBLE_Q_OFF && fg == 1)
            data.i++ ;
        if(str[data.i] == '$' && (data.flag1 == SINGLE_Q_OFF || fg != 1))
		  	expande(str ,&data ,info,trash);
        else
        {
            data.str[data.len] = str[data.i];
            data.len++;
        }
        data.i++;
    }
    return data.str;    
}
// "ls" "ohammou-" ">" "<"