/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:33:03 by ohammou-          #+#    #+#             */
/*   Updated: 2024/07/24 14:18:37 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	c_len(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[data->i][i] != '=')
		i++;
	return (i);
}

void	not_find(t_data *info, t_data *data, int i, t_trash **trash)
{
	if (!check_befor_dollar(info, i) && info->n == 1)
	{
		if (info->len == 0)
		{
			info->str = ft_strdup("true");
			add_to_trash(info->str, trash);
		}
		else
		{
			data->str = ftmalloc(info->j - i + 4 + 1, trash);
			ft_strlcpy(data->str, info->str, info->len + 1);
			ft_strlcat(data->str, "true", info->len + 5);
			info->str = data->str;
		}
		info->len = ft_strlen(info->str);
	}
	else
	{
		data->str = ftmalloc(info->j - i + 1, trash);
		ft_strlcpy(data->str, info->str, info->len + 1);
		info->str = data->str;
	}
	info->i += i - 1;
	info->j -= i;
}

void	etc_of_expande(t_data *data, t_data *info, int i, t_trash **trash)
{
	char	*src;
	int		f;

	while (data->env[data->i])
	{
		f = c_len(data);
		src = ft_substr(data->env[data->i], 0, f);
		add_to_trash(src, trash);
		if (ft_strncmp(data->s, src, ft_strlen(src) + 1) == 0)
		{
			data->src = ft_substr(data->env[data->i], f + 1,
					ft_strlen(data->env[data->i]) - f - 1);
			if (info->flag == DOUBLE_Q_OFF && info->flag2 == 1)
				data->src = add_qoutes(data->src);
			data->str = ftmalloc(info->j - i + ft_strlen(data->src) + 1, trash);
			ft_strlcpy(data->str, info->str, info->len + 1);
			ft_strlcat(data->str, data->src, info->len + ft_strlen(data->src)
				+ 1);
			info->j = info->j - i + ft_strlen(data->src);
			info->len += ft_strlen(data->src);
			return (info->str = data->str, info->i += i - 1, free(data->src));
		}
		data->i++;
	}
	not_find(info, data, i, trash);
}

void	expand_status_exit(t_data *info, t_trash **trash)
{
	t_data	data;

	info->nb = g_exit_status;
	data.src = ft_itoa(info->nb);
	add_to_trash(data.src, trash);
	data.str = malloc(info->j - 2 + ft_strlen(data.src) + 1);
	ft_bzero(data.str, info->j - 2 + ft_strlen(data.src) + 1);
	add_to_trash(data.str, trash);
	ft_strlcpy(data.str, info->str, info->len + 1);
	ft_strlcat(data.str, data.src, info->len + ft_strlen(data.src) + 1);
	info->str = data.str;
	info->i += 1;
	info->j = info->j - 2 + ft_strlen(data.src);
	info->len += ft_strlen(data.src);
}

void	expande(char *str, t_data *info, t_data *data, t_trash **trash)
{
	int	i;

	i = 0;
	data->i = 0;
	if (str[info->i + 1])
		i++;
	if (str[info->i + 1] == '?')
		return (expand_status_exit(info, trash));
	while (ft_isalnum(str[info->i + i]) || str[info->i + i] == '_')
		i++;
	if (str[info->i + i] != '\0')
		data->s = ft_substr(str + 1, info->i, i - 1);
	else
		data->s = ft_substr(str + 1, info->i, i);
	if (data->s[0])
		etc_of_expande(data, info, i, trash);
	else
	{
		info->str[info->len] = '$';
		info->len++;
	}
	free(data->s);
}
