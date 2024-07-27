/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_part2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 08:51:13 by iahamdan          #+#    #+#             */
/*   Updated: 2024/07/25 12:03:42 by iahamdan         ###   ########.fr       */
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