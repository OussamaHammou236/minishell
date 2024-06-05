/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:33:03 by ohammou-          #+#    #+#             */
/*   Updated: 2024/06/04 21:12:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//int g_i;

int c_len(t_data *data)
{
	int i;
	i = 0;
	while(data->env[data->i][i] != '=')
		i++;
	return i;
}

void not_find(t_data *info,t_data *data,int i)
{
	data->str = malloc(info->j - i + 1);
	ft_strlcpy(data->str,info->str,info->len + 1);
	free(info->str);
	info->str = data->str;
	info->str[info->j - i] = '\0';
	info->i += i;
	info->j -= i;
}

void etc_of_expande(t_data *data,t_data *info,int i,char *s)
{
	char *src;
	int f;

	while(data->env[data->i])
	{
		f = c_len(data);
		src = ft_substr(data->env[data->i],0,f);
		if(ft_strncmp(s,src,ft_strlen(s)) == 0)
		{
			data->src = ft_substr(data->env[data->i],f + 1,ft_strlen(data->env[data->i]) - f -1);
			data->str = malloc(info->j - i + ft_strlen(data->src)  + 1);
			data->str[info->j - i + ft_strlen(data->src)] = '\0';
			ft_strlcpy(data->str,info->str,info->len + 1);
			ft_strlcat(data->str,data->src,info->len + ft_strlen(data->env[data->i]) - f);
			free(info->str);
			info->str = data->str;
			info->i += i;
			info->j = info->j - i + ft_strlen(data->src);
			info->len += ft_strlen(data->src);
			return ;
		}
		free(src);
		data->i++;
	}
	not_find(info,data,i);
}

void expqnd_status_exit(t_data *info)
{
	t_data data;

	info->nb = 50;
	data.src = ft_itoa(info->nb);
	data.str = malloc(info->j - 2 + ft_strlen(data.src) + 1);
	data.str[info->j - 2 + ft_strlen(data.src)] = '\0';
	ft_strlcpy(data.str,info->str,info->len + 1);
	ft_strlcat(data.str,data.src,info->len + ft_strlen(data.src) + 1);
	free(info->str);
	info->str = data.str;
	info-> i += 2;
	info->j = info->j - 2 + ft_strlen(data.src);
	info->len += ft_strlen(data.src);
}
void expande(char *str,t_data *info,t_data *data)
{
	int i;
	char *s;

	i = 0;
	data->i = 0;
	if(str[info->i + 1])
		i++;
	if(str[info->i + 1] == '?')
	{
		expqnd_status_exit(info);
		return ;
	}
	while((str[info->i + i] > 'a' &&  str[info->i + i] < 'z') || (str[info->i + i] > 'A' &&  str[info->i + i] < 'Z') ||
		(str[info->i + i] > '0' &&  str[info->i + i] < '9'))
			i++;
	if(str[info->i + i] != '\0')
		s = ft_substr(str + 1,info->i,i - 1);
	else
		s = ft_substr(str + 1,info->i,i);
	if(s[0])
		etc_of_expande(data,info,i,s);
}
