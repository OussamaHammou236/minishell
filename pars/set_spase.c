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

#include "../header.h"

void	double_single_q(t_data *data, char c)
{
	if (data->flag == DOUBLE_Q_OFF && data->flag1 == SINGLE_Q_OFF && c == '"')
		data->flag = DOUBLE_Q_ON;
	else if (data->flag == DOUBLE_Q_ON && c == '"')
		data->flag = DOUBLE_Q_OFF;
	if (data->flag == DOUBLE_Q_OFF && data->flag1 == SINGLE_Q_OFF && c == '\'')
		data->flag1 = SINGLE_Q_ON;
	else if (data->flag1 == SINGLE_Q_ON && c == '\'')
		data->flag1 = SINGLE_Q_OFF;
}

int	edit_line(char *str)
{
	t_data	data;

	initialization_data(&data, 0);
	while (str[data.i])
	{
		double_single_q(&data, str[data.i]);
		if (data.flag == DOUBLE_Q_OFF && data.flag1 == SINGLE_Q_OFF)
		{
			if ((str[data.i] == '>' && str[data.i + 1] == '>')
				|| (str[data.i] == '<' && str[data.i + 1] == '<'))
			{
				data.len += 3;
				data.i++;
			}
			else if ((str[data.i] == '>' && str[data.i + 1] != '>')
				|| (str[data.i] == '<' && str[data.i + 1] != '<')
				|| str[data.i] == '|')
				data.len += 2;
		}
		data.len++;
		data.i++;
	}
	return (data.len);
}

int	check_syntax_error(t_data data)
{
	data.i = 0;
	data.flag = DOUBLE_Q_OFF;
	data.flag1 = SINGLE_Q_OFF;
	while (data.str[data.i])
	{
		double_single_q(&data, data.str[data.i]);
		data.i++;
	}
	if (data.flag == DOUBLE_Q_ON || data.flag1 == SINGLE_Q_ON)
		return (printf("minishell : syntax error\n"), -1);
	return (0);
}

void	etc(t_data *data, char *str)
{
	if ((str[data->i] == '>' && str[data->i + 1] == '>') || (str[data->i] == '<'
			&& str[data->i + 1] == '<'))
	{
		data->str[data->len] = ' ';
		data->str[data->len + 1] = str[data->i];
		data->str[data->len + 2] = str[data->i + 1];
		data->str[data->len + 3] = ' ';
		data->len += 3;
		data->i++;
	}
	else if ((str[data->i] == '>' && str[data->i + 1] != '>')
		|| (str[data->i] == '<' && str[data->i + 1] != '<')
		|| (str[data->i] == '|'))
	{
		data->str[data->len] = ' ';
		data->str[data->len + 1] = str[data->i];
		data->str[data->len + 2] = ' ';
		data->len += 2;
	}
	else if (is_white_space(str[data->i]))
		data->str[data->len] = ' ';
	else
		data->str[data->len] = str[data->i];
}

char	*set_spase(char *str)
{
	t_data	data;

	data.i = 0;
	data.flag = DOUBLE_Q_OFF;
	data.flag1 = SINGLE_Q_OFF;
	data.len = edit_line(str);
	data.str = malloc(data.len + 1);
	if (!data.str)
		return (NULL);
	ft_bzero(data.str, data.len + 1);
	data.len = 0;
	while (str[data.i])
	{
		double_single_q(&data, str[data.i]);
		if (data.flag == DOUBLE_Q_OFF && data.flag1 == SINGLE_Q_OFF)
			etc(&data, str);
		else
			data.str[data.len] = str[data.i];
		data.len++;
		data.i++;
	}
	return (data.str);
}
