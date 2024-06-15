/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:44:35 by ohammou-          #+#    #+#             */
/*   Updated: 2024/06/14 19:45:31 by ohammou-         ###   ########.fr       */
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

char *expand_str(char *str, t_trash **trash, t_data *info)
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
        if(str[data.i] == '$' && data.flag1 == SINGLE_Q_OFF)
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