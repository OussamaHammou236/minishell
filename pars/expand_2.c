/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:44:35 by ohammou-          #+#    #+#             */
/*   Updated: 2024/07/24 10:07:44 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	*ftmalloc(int len, t_trash **trash)
{
	char	*str;

	str = malloc(len);
	ft_bzero(str, len);
	add_to_trash(str, trash);
	return (str);
}

char	*add_qoutes(char *str)
{
	t_data	data;

	data.i = 0;
	data.j = 1;
	data.len = ft_strlen(str) + (cont_words(str, ' ') * 2);
	data.str = malloc(data.len + 1);
	ft_bzero(data.str, data.len + 1);
	data.str[0] = '"';
	while (str[data.i])
	{
		if (str[data.i] != ' ' && str[data.i + 1] == ' ')
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
	return (free(str), data.str);
}

void	initialization_data(t_data *data, int fg)
{
	data->flag = DOUBLE_Q_OFF;
	data->flag1 = SINGLE_Q_OFF;
	data->len = 0;
	data->i = 0;
	data->flag2 = fg;
	data->fg = 0;
	data->v = 0;
	data->n = fg;
}

void	flag_of_expand_herdoc(t_data *data, char *str)
{
	if (str[data->i] != '$' && str[data->i] != ' '
		&& str[data->i] != '<' && str[data->i + 1] != '<'
		&& data->flag1 == SINGLE_Q_OFF && data->flag == DOUBLE_Q_OFF)
		data->fg = 0;
	else if (str[data->i] != '$' && str[data->i] != ' '
		&& (str[data->i] != '<' || str[data->i] != '>')
		&& data->flag1 == SINGLE_Q_OFF && data->flag == DOUBLE_Q_OFF)
		data->fg = 0;
	if (data->v == 1)
		data->fg = 0;
	else if (data->v == 0 && str[data->i] == '$'
		&& data->flag1 == SINGLE_Q_OFF && data->flag == DOUBLE_Q_OFF)
		data->v = 1;
	if (str[data->i] == '<' && str[data->i + 1] == '<'
		&& data->flag1 == SINGLE_Q_OFF && data->flag == DOUBLE_Q_OFF)
		data->fg = 1;
	else if ((str[data->i] == '<' || str[data->i] == '>')
		&& data->flag1 == SINGLE_Q_OFF && data->flag == DOUBLE_Q_OFF)
		data->fg = 1;
}

char	*expand_str(char *str, t_trash **trash, t_data *info, int fg)
{
	t_data	data;

	initialization_data(&data, fg);
	data.sm = str;
	data.j = ft_strlen(str);
	data.str = ftmalloc(data.j + 1, trash);
	while (str[data.i])
	{
		double_single_q(&data, str[data.i]);
		flag_of_expand_herdoc(&data, str);
		if (str[data.i] == '$' && (str[data.i + 1] == '"'
				|| str[data.i + 1] == '\'') && data.flag == DOUBLE_Q_OFF
			&& data.flag1 == SINGLE_Q_OFF && fg == 1)
			data.i += 0;
		else if (str[data.i] == '$' && (data.flag1 == SINGLE_Q_OFF || fg != 1)
			&& (data.fg == 0 || data.flag == DOUBLE_Q_ON))
			expande(str, &data, info, trash);
		else
		{
			data.str[data.len] = str[data.i];
			data.len++;
		}
		data.i++;
	}
	return (data.str);
}
