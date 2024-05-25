/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:33:03 by ohammou-          #+#    #+#             */
/*   Updated: 2024/05/25 20:33:21 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
void expande(char *str,t_data *info,t_data *data)
{
	int i;
	char *s;

	i = 0;
	data->i = 0;
	while(str[info->i + i] != ' ' && str[info->i + i] != '"' && str[info->i + i] != '\'' && str[info->i + i] != '\0')
		i++;
	if(str[info->i + i] == ' ' || str[info->i + i] == '"' || str[info->i + i] == '\'')
		s = ft_substr(str + 1,info->i,i - 1);
	else
		s = ft_substr(str + 1,info->i,i);
	etc_of_expande(data,info,i,s);
}
