/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 00:24:19 by iahamdan          #+#    #+#             */
/*   Updated: 2024/07/19 11:23:38 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	cmp_str(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1 || !str2)
		return (0);
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}

char	**duplacte_env(char **env)
{
	int		i;
	char	**our_env;

	i = 0;
	while (env[i])
		i++;
	our_env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		our_env[i] = ft_strdup(env[i]);
		i++;
	}
	our_env[i] = NULL;
	return (our_env);
}

int	get_exit_status(int status)
{
	return (status / 256);
}

char	*new_path_cmd(char *cmd)
{
	char	*our_path;
	int		len_path;
	int		i;

	i = 2;
	len_path = ft_strlen(cmd);
	our_path = malloc(sizeof(char) * (len_path + 3));
	our_path[0] = '_';
	our_path[1] = '=';
	while (i - 2 < len_path)
	{
		our_path[i] = cmd[i - 2];
		i++;
	}
	our_path[i] = '\0';
	return (our_path);
}

void	change_cmd_var_env(t_data *info, char **cmd)
{
	int		i;
	int		posi;
	
	if (!cmd[0] || !info->env[0])
		return ;
	posi = 0;
	i = 0;
	while (info->env[i])
		i++;
	posi = i - 1;
	free(info->env[posi]);
	i = 0;
	while (cmd[i])
		i++;
	info->env[posi] = new_path_cmd(cmd[i - 1]);
}