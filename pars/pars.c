/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:54:06 by ohammou-          #+#    #+#             */
/*   Updated: 2024/07/04 18:02:24 by oumondad         ###   ########.fr       */
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

void	etc_change(t_input **list, t_data *data, t_trash **trash)
{
	int	i;

	i = 0;
	while (data->cmd[data->len][i])
	{
		if ((data->cmd[data->len][i] == '>' || data->cmd[data->len][i] == '<')
			&& data->cmd[data->len + 1])
		{
			(*list)->red[data->i] = ft_strdup(data->cmd[data->len]);
			(*list)->red[data->i + 1] = change_cmd(data->cmd[data->len + 1],
					len(data->cmd[data->len + 1]), trash);
			add_to_trash((*list)->red[data->i], trash);
			data->len++;
			data->i += 2;
			return ;
		}
		else
		{
			(*list)->cmd[data->j] = change_cmd(data->cmd[data->len],
					len(data->cmd[data->len]), trash);
			data->j++;
			return ;
		}
		i++;
	}
}

void	change(t_input **list, char **cmd, t_trash **trash)
{
	t_data	data;

	data.i = 0;
	data.j = 0;
	data.len = 0;
	data.cmd = cmd;
	while (cmd[data.len])
	{
		etc_change(list, &data, trash);
		data.len++;
	}
}

void	command(char *line, t_input **list, t_trash **trash)
{
	int		j;
	char	**cmd;
	t_input	*node;

	j = 0;
	cmd = ft_mini_split(line, '|', trash);
	while (cmd[j])
	{
		node = ft_lstnew(cmd);
		add_to_trash(node, trash);
		check_tocken(cmd[j], &node, 1, trash);
		change(&node, ft_mini_split(cmd[j], ' ', trash), trash);
		ft_lstadd_back(list, node);
		j++;
	}
}
