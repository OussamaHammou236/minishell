/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_part_four.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:34:14 by iahamdan          #+#    #+#             */
/*   Updated: 2024/08/06 22:43:02 by iahamdan         ###   ########.fr       */
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
	unlink("/var/tmp/.h");
	i = 0;
	while (i < info->flags.number_files)
	{
		free(info->flags.names[i]);
		i++;
	}
}

void	handle_status_pip(int st)
{
	if (st == 0)
		ft_status(0, 0);
	else if (st == 256)
		ft_status(1, 0);
	else if (st == 512)
		ft_status(2, 0);
	else if (st == 768)
		ft_status(125, 0);
	else if (st == 1024)
		ft_status(127, 0);
	else if (st == 1280 || st == 2)
		ft_status(130, 0);
	else if (st == 1536)
		ft_status(126, 0);
}
