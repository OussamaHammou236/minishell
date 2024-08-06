/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 09:36:21 by ohammou-          #+#    #+#             */
/*   Updated: 2024/08/06 11:38:53 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	check_befor_dollar(t_data *info, int i)
{
	int	c;

	c = i;
	while (info->i + c > 0 && info->sm[info->i + c] != '$')
		c--;
	c--;
	while (info->i + c > 0 && info->sm[info->i + c] != '|')
	{
		if (info->sm[info->i + c] != ' ' && info->sm[info->i + c] != '|')
			return (-1);
		c--;
	}
	while (info->sm[info->i + i] && info->sm[info->i + i] != '|')
	{
		if (info->sm[info->i + i] != ' ' && info->sm[info->i + i] != '|')
			return (-1);
		i++;
	}
	return (0);
}

void	check_imbg(t_input **list, t_data *data, t_trash **trash, t_data *info)
{
	char	*s;

	if (data->cmd[data->len][0] == '<' && data->cmd[data->len][1] == '<'
		&& (ft_strchr(data->cmd[data->len + 1], '"')
		|| ft_strchr(data->cmd[data->len + 1], '\'')) && data->n < (*list)->len)
		(*list)->is_qouts[data->n] = 1;
	add_to_trash((*list)->red[data->i], trash);
	if (data->cmd[data->len + 1][0] == '$' && data->cmd[data->len][1] != '<')
	{
		s = expand_str(data->cmd[data->len + 1], trash, info, 0);
		if (red_check(s) == -1)
		{
			printf("minishell: %s: ambiguous redirect\n",
				data->cmd[data->len + 1]);
			ft_status(1, 0);
			s = NULL;
		}
		(*list)->red[data->i + 1] = edit_str(s, trash);
	}
	else
		(*list)->red[data->i + 1] = change_cmd(data->cmd[data->len + 1],
				len(data->cmd[data->len + 1]), trash);
	data->n++;
	data->len++;
	data->i += 2;
}
