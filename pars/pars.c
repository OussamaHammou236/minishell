/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:54:06 by ohammou-          #+#    #+#             */
/*   Updated: 2024/07/27 21:07:14 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	len(char *str)
{
	t_data	data;

	data.flag = DOUBLE_Q_OFF;
	data.flag1 = SINGLE_Q_OFF;
	data.len = 0;
	data.i = 0;
	while (1)
	{
		double_single_q(&data, str[data.i]);
		if ((data.flag1 == SINGLE_Q_ON && str[data.i] == '\'')
			|| (data.flag == DOUBLE_Q_ON && str[data.i] == '"'))
			data.i++;
		if (!str[data.i])
			break ;
		if (data.flag == DOUBLE_Q_ON || data.flag1 == SINGLE_Q_ON
			|| (str[data.i] != '"' && str[data.i] != '\''))
			data.len++;
		data.i++;
	}
	return (data.len);
}

char	*change_cmd(char *str, int len, t_trash **trash)
{
	t_data	data;

	data.flag = DOUBLE_Q_OFF;
	data.flag1 = SINGLE_Q_OFF;
	data.i = 0;
	data.j = len;
	data.str = malloc(len + 1);
	if (!data.str)
		return NULL;
	add_to_trash(data.str, trash);
	ft_bzero(data.str, len + 1);
	data.len = 0;
	while (str[data.i])
	{
		double_single_q(&data, str[data.i]);
		if ((data.flag == DOUBLE_Q_ON && str[data.i] != '"')
			|| (data.flag1 == SINGLE_Q_ON && str[data.i] != '\'')
			|| (str[data.i] != '"' && str[data.i] != '\''))
		{
			data.str[data.len] = str[data.i];
			data.len++;
		}
		data.i++;
	}
	return (data.str);
}

void	etc_change(t_input **list, t_data *data, t_trash **trash, t_data *info)
{
	int	i;

	i = 0;
	while (data->cmd[data->len][i])
	{
		if ((data->cmd[data->len][i] == '>' || data->cmd[data->len][i] == '<')
			&& data->cmd[data->len + 1])
		{
			if (data->n < (*list)->len)
				(*list)->is_qouts[data->n] = 0;
			check_imbg(list, data, trash, info);
			return ;
		}
		else
		{
			(*list)->cmd[data->j] = change_cmd(data->cmd[data->len],
					len(data->cmd[data->len]), trash);
			if (!(*list)->cmd[data->j])
				return ;
			data->j++;
			return ;
		}
		i++;
	}
}

void	change(t_input **list, char **cmd, t_trash **trash, t_data *info)
{
	t_data	data;

	data.i = 0;
	data.j = 0;
	data.len = 0;
	data.cmd = cmd;
	data.n = 0;
	while (cmd[data.len])
	{
		etc_change(list, &data, trash, info);
		data.len++;
	}
}

void	command(char *line, t_input **list, t_trash **trash, t_data *info)
{
	int		j;
	char	**cmd;
	t_input	*node;

	j = 0;
	cmd = ft_mini_split(line, '|', trash);
	while (cmd[j])
	{
		node = ft_lstnew();
		add_to_trash(node, trash);
		check_tocken(cmd[j], &node, 1, trash);
		change(&node, ft_mini_split(cmd[j], ' ', trash), trash, info);
		ft_lstadd_back(list, node);
		j++;
	}
}
