/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:56:42 by ohammou-          #+#    #+#             */
/*   Updated: 2024/07/04 17:34:08 by oumondad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	cont_words(char *str, char sp)
{
	t_data	data;

	data.i = 0;
	data.j = 0;
	data.flag = DOUBLE_Q_OFF;
	data.flag1 = SINGLE_Q_OFF;
	while (str[data.i])
	{
		if (str[data.i] && str[data.i] != sp)
		{
			if (data.flag == DOUBLE_Q_OFF && data.flag1 == SINGLE_Q_OFF)
				data.j++;
			while (str[data.i] && str[data.i] != sp)
			{
				double_single_q(&data, str[data.i]);
				data.i++;
			}
		}
		else
			data.i++;
	}
	return (data.j);
}

int	len_of_words(char *str, char sp)
{
	t_data	data;

	data.i = 0;
	data.flag = DOUBLE_Q_OFF;
	data.flag1 = SINGLE_Q_OFF;
	while (str[data.i])
	{
		if (data.flag == DOUBLE_Q_OFF && data.flag1 == SINGLE_Q_OFF
			&& str[data.i] == '"')
			data.flag = DOUBLE_Q_ON;
		else if (data.flag == DOUBLE_Q_ON && str[data.i] == '"')
			data.flag = DOUBLE_Q_OFF;
		if (data.flag == DOUBLE_Q_OFF && data.flag1 == SINGLE_Q_OFF
			&& str[data.i] == '\'')
			data.flag1 = SINGLE_Q_ON;
		else if (data.flag1 == SINGLE_Q_ON && str[data.i] == '\'')
			data.flag1 = SINGLE_Q_OFF;
		else if (data.flag == DOUBLE_Q_OFF && data.flag1 == SINGLE_Q_OFF
			&& str[data.i] == sp)
			return (data.i);
		data.i++;
	}
	return (data.i);
}

void	initialization_of_sp(t_data *data, t_trash **trash, char sp, char *str)
{
	data->i = 0;
	data->len = cont_words(str, sp);
	data->cmd = malloc((data->len + 1) * sizeof(char *));
	add_to_trash(data->cmd, trash);
	data->cmd[data->len] = NULL;
}

char	**ft_mini_split(char *str, char sp, t_trash **trash)
{
	int		j;
	t_data	data;

	initialization_of_sp(&data, trash, sp, str);
	while (data.i < data.len && *str)
	{
		while (*str && *str == sp)
			str++;
		j = len_of_words(str, sp);
		data.cmd[data.i] = malloc(j + 1);
		ft_strlcpy(data.cmd[data.i], str, j + 1);
		add_to_trash(data.cmd[data.i], trash);
		str += j;
		data.i++;
	}
	return (data.cmd);
}
