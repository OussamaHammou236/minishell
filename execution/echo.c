/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:41:03 by iahamdan          #+#    #+#             */
/*   Updated: 2024/07/30 18:39:58 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	run_echo(t_data *info, t_input temp)
{
	int	len_input;
	int	i;

	len_input = get_part_input(info, temp);
	i = 1;
	if (len_input == 1)
		printf("\n");
	else
	{
		if (cmp_str(temp.cmd[1], "-n") == 1)
			i++;
		while (temp.cmd[i])
		{
			printf("%s", temp.cmd[i]);
			if (temp.cmd[i + 1])
				printf(" ");
			i++;
		}
		if (cmp_str(temp.cmd[1], "-n") != 1)
			printf("\n");
	}
	g_data.exit_status = 0;
}
