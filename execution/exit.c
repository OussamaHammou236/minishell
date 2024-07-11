/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:05:58 by iahamdan          #+#    #+#             */
/*   Updated: 2024/07/09 01:07:32 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	is_all_numbers(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	part_two_exit(t_data *info, t_input temp, int len_input, int store)
{
	if (is_all_numbers(temp.cmd[1]) == 0)
	{
		if (len_input != 2)
		{
			write(2, "exit: too many arguments\n", 25);
			g_exit_status = 1;
			return (1);
		}
		else
		{
			store = ft_atoi(temp.cmd[1]);
			free_something_after_exit(info);
			exit(store);
		}
	}
	else
	{
		error_print("minishell: exit: ", temp.cmd[1],
			": numeric argument required\n", NULL);
		free_something_after_exit(info);
		exit(2);
	}
	return (0);
}

void	run_exit(t_data *info, t_input temp)
{
	int	len_input;
	int	store;

	store = 0;
	len_input = get_part_input(info, temp);
	if (len_input > 1)
	{
		if (part_two_exit(info, temp, len_input, store) == 1)
			return ;
	}
	free_something_after_exit(info);
	printf("exit\n");
	exit(0);
}
