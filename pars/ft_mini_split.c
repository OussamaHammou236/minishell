/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:56:42 by ohammou-          #+#    #+#             */
/*   Updated: 2024/05/14 15:11:14 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int cont_words(char *str,char sp)
{
	int i;
	int j;
	int flag;

	i = 0;
	j = 0;
	flag = DOUBLE_Q_OFF;
	int flag2 = SINGLE_Q_OFF;
	while(str[i])
	{
		if(str[i] && str[i] != sp)
		{
			if(flag == DOUBLE_Q_OFF && flag2 == SINGLE_Q_OFF)
				j++;
			while(str[i] && str[i] != sp)
			{
				if(flag == DOUBLE_Q_OFF && flag2 == SINGLE_Q_OFF && str[i] == '"')
				{
					flag = DOUBLE_Q_ON;
					i++;
				}
				if(flag == DOUBLE_Q_ON && str[i] == '"')
					flag = DOUBLE_Q_OFF;
				if(flag == DOUBLE_Q_OFF && flag2 == SINGLE_Q_OFF && str[i] == 39)
				{
					flag2 = SINGLE_Q_ON;
					i++;
				}
				if(flag2 == SINGLE_Q_ON && str[i] == 39)
					flag2 = SINGLE_Q_OFF;
				i++;
			}
		}
		else
			i++;
	}
	return j;
}

int len_of_words(char *str,char sp)
{
	t_data data;
	data.i = 0;
	data.flag = DOUBLE_Q_OFF;
	data.flag2 = SINGLE_Q_OFF;
	while(str[data.i])
	{
		if(data.flag == DOUBLE_Q_OFF && data.flag2 == SINGLE_Q_OFF && str[data.i] == '"')
		{
			data.flag = DOUBLE_Q_ON;
			data.i++;
		}
		if(data.flag == DOUBLE_Q_ON && str[data.i] == '"')
			data.flag = DOUBLE_Q_OFF;
		if(data.flag == DOUBLE_Q_OFF && data.flag2 == SINGLE_Q_OFF && str[data.i] == 39)
		{
			data.flag2 = SINGLE_Q_ON;
			data.i++;
		}
		if(data.flag2 == SINGLE_Q_ON && str[data.i] == 39)
			data.flag2 = SINGLE_Q_OFF;
		if(data.flag == DOUBLE_Q_OFF && data.flag2 == SINGLE_Q_OFF && str[data.i] == sp)
			return data.i + 1;
		data.i++;
	}
	return data.i;
}

char **ft_mini_split(char *str,char sp)
{
	int j;
	t_data data;
	data.i = 0;
	data.len = cont_words(str,sp);
	data.cmd = malloc((data.len + 1) * sizeof(char *));
	data.cmd[data.len] = NULL;
	while(data.i < data.len && *str)
	{
		while(*str && *str == sp)
			str++;
		j = len_of_words(str,sp);
		if(*(str + j - 1) != sp)
		{
			data.cmd[data.i] = malloc(j + 1);
			ft_strlcpy(data.cmd[data.i],str,j + 1);
		}
		else
		{
			data.cmd[data.i] = malloc(j);
		 	ft_strlcpy(data.cmd[data.i],str,j);
		}
		str += j;
		data.i++;
	}
	return data.cmd;
}

