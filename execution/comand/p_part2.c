/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_part2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 08:51:13 by iahamdan          #+#    #+#             */
/*   Updated: 2024/08/06 15:28:30 by iahamdan         ###   ########.fr       */
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

int	check_if_is_dir(char *input, t_data *info)
{
	struct stat	statbuf;

	if (info->flags.unset_path == 0)
	{
		if (search_for_character(input, '/') == 0)
			return (0);
	}
	if (stat(input, &statbuf) == 0)
	{
		if (S_ISDIR(statbuf.st_mode))
			return (1);
	}
	return (0);
}
