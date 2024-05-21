/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:33:03 by ohammou-          #+#    #+#             */
/*   Updated: 2024/05/18 20:36:18 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
  
void expande(char *str,t_data *info,t_data *data)
{
	int i;
	char *s;

	i = 0;
	while(str[info->i + i] != ' ' && str[info->i + i] != '"' && str[info->i + i] != '\'' && str[info->i + i] != '\0')
		i++;
	s = ft_substr(str + 1,info->i,i);
	data->i = 0;
	while(data->env[data->i])
	{
		if(ft_strncmp(s,data->env[data->i],i - 1) == 0)
			printf("%s\n",data->env[data->i]);
		// printf("%s\n",data->env[data->i]);
		data->i++;
	}
}