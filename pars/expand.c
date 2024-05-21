/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:33:03 by ohammou-          #+#    #+#             */
/*   Updated: 2024/05/21 21:17:57 by ohammou-         ###   ########.fr       */
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
void expande(char *str,t_data *info,t_data *data)
{
	int i;
	char *s;
	char *src;
	int f;
	data->f = 0;
	i = 0;
	while(str[info->i + i] != ' ' && str[info->i + i] != '"' && str[info->i + i] != '\'' && str[info->i + i] != '\0')
		i++;
	if(str[info->i + i] == ' ' && str[info->i + i] == '"')
		data->f = 1;
	s = ft_substr(str + 1,info->i,i);
	data->i = 0;
	while(data->env[data->i])
	{
		f = c_len(data);
		src = ft_substr(data->env[data->i],0,f);
		if(ft_strncmp(s,src,ft_strlen(src)) == 0)
		{
			data->src = ft_substr(data->env[data->i],f + 1,ft_strlen(data->env[data->i]) - f -1);
			data->str = malloc(info->j - i + ft_strlen(data->env[data->i]) - f + 1);
			ft_strlcpy(data->str,info->str,info->len);
			ft_strlcat(data->str,data->src,info->len + ft_strlen(data->env[data->i]) - f);
			free(info->str);
			info->str = data->str;
			info->i += i;
			info->len += ft_strlen(info->str);
			return ;
		}
		free(src);
		data->i++;
	}
}
