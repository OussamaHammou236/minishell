/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_part2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 08:51:13 by iahamdan          #+#    #+#             */
/*   Updated: 2024/07/14 08:51:45 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	check_if_path_exist(t_data *info)
{
	int	i;

	i = 0;
	while (info->env[i])
	{
		if (cmp_str_env(info->env[i], "PATH=", 5) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	check_path(t_data *info, char *input)
{
	if (check_if_path_exist(info) == 1)
	{
		info->flags.unset_path = 0;
		return (0);
	}
	error_print("minishell: ", input, ": No such file or directory\n", NULL);
	g_exit_status = 127;
	info->flags.unset_path = 1;
	return (1);
}
