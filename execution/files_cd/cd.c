/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:23:29 by iahamdan          #+#    #+#             */
/*   Updated: 2024/08/02 22:16:27 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	check_specifique_case(t_input temp)
{
	int	i;

	i = 0;
	while (temp.cmd[1][i])
	{
		if (temp.cmd[1][i] != 126)
			return (0);
		i++;
	}
	return (1);
}

int	run_cd_part(t_data *info)
{
	if (chdir(get_home(info)) == -1)
	{
		ft_status(1, 0);
		return (-1);
	}
	ft_status(0, 0);
	return (0);
}

int	run_cd_part_two(t_data *info)
{
	if (chdir(get_home(info)) == -1)
	{
		ft_status(1, 0);
		return (-1);
	}
	ft_status(0, 0);
	return (0);
}

int	run_cd(t_data *info, t_input temp)
{
	int	len_input;

	len_input = get_part_input(temp);
	if (len_input == 1)
	{
		if (run_cd_part(info) == -1)
			return (-1);
	}
	else if (len_input == 2)
	{
		if (check_specifique_case(temp) == 1)
		{
			if (run_cd_part_two(info) == -1)
				return (-1);
		}
		else
			return (part_two_run_cd(info, temp));
	}
	else
	{
		error_print("minishell: cd: too many arguments\n", NULL, NULL, NULL);
		ft_status(1, 0);
	}
	return (0);
}
