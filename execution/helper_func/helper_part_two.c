/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_part_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 00:24:57 by iahamdan          #+#    #+#             */
/*   Updated: 2024/07/04 00:24:58 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	shlvl_increament(t_data *info)
{
	int		i;
	char	*new_shlvl;

	i = 0;
	while (info->env[i])
	{
		if (cmp_str_env(info->env[i], "SHLVL=", 6) == 1)
		{
			new_shlvl = make_new_shlvl(info, i);
			free(info->env[i]);
			info->env[i] = new_shlvl;
			return ;
		}
		i++;
	}
}

void	initialization(t_data *info)
{
	info->flags.is_builtin_cmd = 0;
	info->number_cmd = 0;
	info->flags.fd_stdout = dup(1);
	info->flags.fd_stdin = dup(0);
	info->flags.dup_stdin_used = 0;
	info->flags.dup_stdout_used = 0;
	info->flag_free_current_path = 0;
	shlvl_increament(info);
}

int	cmp_str_env(char *str1, const char *str2, int len_str2)
{
	int	i;

	i = 0;
	while (i < len_str2 && str1[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	if (str1[i] == '\0' && i != len_str2)
		return (0);
	return (1);
}

int	get_part_input(t_data *info, t_input temp)
{
	int	i;

	i = 0;
	while (temp.cmd[i])
	{
		i++;
	}
	return (i);
}

void	extract_path(char **env, t_data *info)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (cmp_str_env(env[i], "PATH=", 5) == 1)
		{
			info->path = ft_split(&env[i][5], ':');
			break ;
		}
		i++;
	}
}
