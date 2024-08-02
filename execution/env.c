/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:43:28 by iahamdan          #+#    #+#             */
/*   Updated: 2024/08/02 22:36:36 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int	check_second_error_env(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (str[0] != '-')
		return (0);
	if (i == 1)
		return (1);
	else if (i == 2)
		if (str[1] == '-')
			return (2);
	return (3);
}

void	part_two_env(t_data *info)
{
	int	i;

	i = 0;
	while (info->env[i])
	{
		if (!info->env[i + 1])
		{
			printf("_=/usr/bin/env\n");
			break ;
		}
		if (is_containe_equal_flag(info->env[i]) == 0)
			printf("%s\n", info->env[i]);
		i++;
	}
	ft_status(0, 0);
}

void	run_env(t_data *info, t_input temp)
{
	int	len_input;
	int	check_error;

	check_error = 0;
	len_input = get_part_input(temp);
	if (len_input > 1)
	{
		check_error = check_second_error_env(temp.cmd[1]);
		if (check_error == 0)
		{
			error_print("env: '", temp.cmd[1], "': No such file or directory\n",
				NULL);
			ft_status(127, 0);
		}
		else if (check_error == 1)
			ft_status(0, 0);
		else if (check_error == 3)
		{
			error_print("env: invalid option -- '", temp.cmd[1], "'\n",
				"Try 'env --help' for more information.\n");
			ft_status(125, 0);
			return ;
		}
	}
	part_two_env(info);
}
