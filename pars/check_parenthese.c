/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parenthese.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:53:19 by ohammou-          #+#    #+#             */
/*   Updated: 2024/05/09 20:58:06 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int len_of_str(char *str)
{
	int i;
	t_data data;
	
	i = 0;
	data.flag = DOUBLE_Q_OFF;
	data.flag1 = SINGLE_Q_OFF;
	data.flag2 =  PARENTHESE_OFF;
	data.len = 0;
	while(str[i])
	{
		double_single_Q(&data,str[i]);
		if((data.flag == DOUBLE_Q_OFF && data.flag1 == SINGLE_Q_OFF && str[i] != '(' &&  str[i] != ')')
			|| (data.flag == DOUBLE_Q_ON || data.flag1 == SINGLE_Q_ON))
			data.len++;
		i++;
	}
	if(data.flag2 == PARENTHESE_ON)
		ft_error("error1");
	return data.len;
}
char *handel_parenthese(char *line)
{
	t_data data;
	int i;
	char *str;
	
	data.flag = DOUBLE_Q_OFF;
	data.flag1 = SINGLE_Q_OFF;
	data.flag2 =  PARENTHESE_OFF;
	i = 0;
	data.len = 0;
	str = malloc(len_of_str(line) + 1);
	while(line[i])
	{
		double_single_Q(&data,line[i]);
		if((data.flag == DOUBLE_Q_OFF && data.flag1 == SINGLE_Q_OFF && line[i] != '(' &&  line[i] != ')')
			|| (data.flag == DOUBLE_Q_ON || data.flag1 == SINGLE_Q_ON))
		{
			str[data.len] = line[i];
			data.len++;
		}
		i++;
	}
	str[data.len] = '\0';
	return set_spase(str);
}
