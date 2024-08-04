/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:23:22 by iahamdan          #+#    #+#             */
/*   Updated: 2024/08/03 22:10:52 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

char	*get_current_path(void)
{
	char	*p;

	p = getcwd(NULL, 0);
	return (p);
}

char	*make_format_path(char *str)
{
	int		i;
	int		len;
	char	*new_path;

	len = ft_strlen(str);
	new_path = manage_malloc_one(len + 5);
	new_path[0] = 'P';
	new_path[1] = 'W';
	new_path[2] = 'D';
	new_path[3] = '=';
	i = 4;
	while (i < len + 4)
	{
		new_path[i] = str[i - 4];
		i++;
	}
	new_path[i] = '\0';
	return (new_path);
}

void	update_old_pwd(t_data *info, char *str)
{
	int		i;
	int		len;
	char	*new_path;

	len = ft_strlen(str);
	new_path = manage_malloc_one(len + 4);
	new_path[0] = 'O';
	new_path[1] = 'L';
	new_path[2] = 'D';
	i = 2;
	while (++i < len + 3)
		new_path[i] = str[i - 3];
	new_path[i] = '\0';
	i = -1;
	while (info->env[++i])
	{
		if (cmp_str_env(info->env[i], "OLDPWD=", 7) == 1)
		{
			free(info->env[i]);
			info->env[i] = new_path;
			return ;
		}
	}
	free(new_path);
}

void	update_env(t_data *info)
{
	char	*new_path;
	int		i;

	new_path = get_current_path();
	if (!new_path)
		return ;
	if (info->flags.store_path_currnt_dir)
		free(info->flags.store_path_currnt_dir);
	info->flags.store_path_currnt_dir = ft_strdup(new_path);
	i = 0;
	while (info->env[i])
	{
		if (cmp_str_env(info->env[i], "PWD=", 4) == 1)
		{
			update_old_pwd(info, info->env[i]);
			free(info->env[i]);
			info->env[i] = make_format_path(new_path);
			free(new_path);
			return ;
		}
		i++;
	}
	free(new_path);
}
