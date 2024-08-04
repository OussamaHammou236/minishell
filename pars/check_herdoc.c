/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_herdoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:16:52 by ohammou-          #+#    #+#             */
/*   Updated: 2024/08/04 17:39:58 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	check_herdoc(t_data *data, t_trash **trash)
{
	t_data	*tmp;
	int		i;

	i = 0;
	while (i < data->len)
	{
		if (data->nb_of_herdoc > 16)
		{
			printf("minishell: maximum here-document count exceeded \n");
			tmp = data_global(data, 1);
			free_env_new(tmp);
			free_trash(trash);
			exit(2);
		}
		else if (data->tab[i] == RE_OUTF)
			data->nb_of_herdoc++;
		i++;
	}
}

int	red_check(char *str, t_trash **trash)
{
	int		i;
	t_data	g_data;

	i = 0;
	g_data.i = 0;
	g_data.j = ft_strlen(str) - 1;
	if (!*str || cont_words_spaces(str) > 1 || cont_words_spaces(str) == 0)
		return (-1);
	while (str[g_data.i] && is_white_space(str[g_data.i]))
		g_data.i++;
	while (g_data.j > g_data.i && is_white_space(str[g_data.j]))
		g_data.j--;
	g_data.str = ft_substr(str, g_data.i, g_data.j - g_data.i + 1);
	add_to_trash(g_data.str, trash);
	return (0);
}

int	set_value(t_data *data, t_data *info, int i, t_trash **trash)
{
	if (info->flag == DOUBLE_Q_OFF && info->flag2 == 1)
		data->src = add_single_double_q(data->src);
	data->str = ftmalloc(info->j - i + ft_strlen(data->src) + 1, trash);
	if (!data->src || !data->str)
		return (info->str = NULL, ft_status(2, 0), 0);
	ft_strlcpy(data->str, info->str, info->len + 1);
	ft_strlcat(data->str, data->src, info->len + ft_strlen(data->src)
		+ 1);
	info->j = info->j - i + ft_strlen(data->src);
	info->len += ft_strlen(data->src);
	return (1);
}
