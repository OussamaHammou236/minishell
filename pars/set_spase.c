/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_spase.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:05:25 by ohammou-          #+#    #+#             */
/*   Updated: 2024/05/09 20:57:59 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void double_single_Q(t_data *data,char c)
{
		if(data->flag == DOUBLE_Q_OFF && data->flag1 == SINGLE_Q_OFF && c == '"')
			data->flag = DOUBLE_Q_ON;
		else if (data->flag == DOUBLE_Q_ON && c == '"')
			data->flag = DOUBLE_Q_OFF;
		if(data->flag == DOUBLE_Q_OFF && data->flag1 == SINGLE_Q_OFF && c == '\'')
			data->flag1 = SINGLE_Q_ON;
		else if (data->flag1 == SINGLE_Q_ON && c == '\'')
			data->flag1 = SINGLE_Q_OFF;
		if(data->flag2 ==  PARENTHESE_OFF && data->flag == DOUBLE_Q_OFF && data->flag1 == SINGLE_Q_OFF && c == '(')
			data->flag2 =  PARENTHESE_ON;
		else if(data->flag2 ==  PARENTHESE_ON && data->flag == DOUBLE_Q_OFF && data->flag1 == SINGLE_Q_OFF && c == ')')
			data->flag2 =  PARENTHESE_OFF;
}

int edit_line(char *str)
{
	t_data data;
	int i;

	i = 0;
	data.flag = DOUBLE_Q_OFF;
	data.flag1 = SINGLE_Q_OFF;
	data.len = 0;
	while(str[i])
	{
		double_single_Q(&data,str[i]);
		if(data.flag == DOUBLE_Q_OFF && data.flag1 == SINGLE_Q_OFF)
		{
			if((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<'))
			{
				data.len += 2;
				i++;
			}
			else if((str[i] == '>' && str[i + 1] != '>') || (str[i] == '<' && str[i + 1] != '<') || 
				(str[i] == '|'))
				data.len += 2;
		}
		data.len++;
		i++;
	}
	return data.len;
}
void etc(t_data *data,char *str)
{
	if((str[data->i] == '>' && str[data->i + 1] == '>') || (str[data->i] == '<' && str[data->i + 1] == '<'))
	{
		data->str[data->len] = ' ';
		data->str[data->len += 1] = str[data->i];
		data->str[data->len += 1] = str[data->i + 1];
		data->str[data->len += 1] = ' ';
		data->i++;
	}
	else if((str[data->i] == '>' && str[data->i + 1] != '>') || (str[data->i] == '<' && str[data->i + 1] != '<')
		|| (str[data->i] == '|'))
	{
		data->str[data->len] = ' ';
		data->str[data->len += 1] = str[data->i];
		data->str[data->len += 1] = ' ';
	}
	else if(str[data->i] >= 9 && str[data->i] <= 13)
		data->str[data->len] = ' ';
	else
		data->str[data->len] = str[data->i];	
}
char *set_spase(char *str)
{
	t_data data;

	data.i = 0;
	data.flag = DOUBLE_Q_OFF;
	data.flag1 = SINGLE_Q_OFF;
	data.len = edit_line(str);
	data.str = malloc(data.len + 1);
	data.str[data.len] = '\0';
	data.len = 0;
	while(str[data.i])
	{
		double_single_Q(&data,str[data.i]);
		if(data.flag == DOUBLE_Q_OFF && data.flag1 == SINGLE_Q_OFF)
			etc(&data,str);
		else
			data.str[data.len] = str[data.i];
		data.len++;
		data.i++;
	}
	return data.str;	
}
