/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:41:03 by iahamdan          #+#    #+#             */
/*   Updated: 2024/08/03 17:07:44 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	echo_compare_opt(char *str)
{
	int	i;
	int	len;

	i = 0;
	while (str[i])
		i++;
	len = i;
	if (len < 2)
		return (0);
	if (str[0] != '-')
		return (0);
	if (str[1] != 'n')
		return (0);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	run_echo(t_input temp)
{
	int	len_input;
	int	i;

	len_input = get_part_input(temp);
	i = 1;
	if (len_input == 1)
		printf("\n");
	else
	{
		if (echo_compare_opt(temp.cmd[1]) == 1)
			i++;
		while (temp.cmd[i])
		{
			printf("%s", temp.cmd[i]);
			if (temp.cmd[i + 1])
				printf(" ");
			i++;
		}
		if (echo_compare_opt(temp.cmd[1]) != 1)
			printf("\n");
	}
	ft_status(0, 0);
}
