/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_part_four.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:34:14 by iahamdan          #+#    #+#             */
/*   Updated: 2024/08/01 16:49:15 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	search_for_character(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	delete_files(t_data *info)
{
	int	i;

	i = 0;
	while (i < info->flags.number_files)
	{
		unlink(info->flags.names[i]);
		i++;
	}
	unlink(".herdoc_buff");
	i = 0;
	while (i < info->flags.number_files)
	{
		free(info->flags.names[i]);
		i++;
	}
}
