/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:05:58 by iahamdan          #+#    #+#             */
/*   Updated: 2024/08/03 16:37:31 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	is_all_numbers(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

void	part_three_exit(t_data *info, t_input temp)
{
	error_print("minishell: exit: ", temp.cmd[1],
		": numeric argument required\n", NULL);
	free_something_after_exit(info);
	printf("exit\n");
	exit(2);
}

int	part_two_exit(t_data *info, t_input temp, int len_input, int store)
{
	if (is_all_numbers(temp.cmd[1]) == 0)
	{
		if (len_input != 2)
		{
			write(2, "exit: too many arguments\n", 25);
			ft_status(1, 0);
			return (1);
		}
		else
		{
			if (handle_long_max(temp.cmd[1]) == -1)
				part_three_exit(info, temp);
			store = ft_atoi(temp.cmd[1]);
			free_something_after_exit(info);
			printf("exit\n");
			exit(store);
		}
	}
	else
		part_three_exit(info, temp);
	return (0);
}

void	run_exit(t_data *info, t_input temp)
{
	int	len_input;
	int	store;

	store = 0;
	len_input = get_part_input(temp);
	if (len_input > 1)
	{
		if (part_two_exit(info, temp, len_input, store) == 1)
			return ;
	}
	free_something_after_exit(info);
	printf("exit\n");
	exit(WEXITSTATUS(ft_status(0, 1) * 256));
}
