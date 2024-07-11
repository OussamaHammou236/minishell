/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:05:51 by iahamdan          #+#    #+#             */
/*   Updated: 2024/07/06 18:03:17 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static int	check_equality(char *str1_env, char *variable)
{
	int	i;

	i = 0;
	while (str1_env[i] != '=')
	{
		if (str1_env[i] != variable[i])
			return (-1);
		i++;
	}
	if (variable[i])
		return (-1);
	return (1);
}

int	check_var_exist(t_data *info, char *str)
{
	int	i;

	i = 0;
	while (info->env[i])
	{
		if (check_equality(info->env[i], str) == 1)
			return (i);
		i++;
	}
	return (-1);
}

static int	check_second_error_unset(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (str[0] != '-')
		return (0);
	else if (i == 2)
		if (str[1] == '-')
			return (2);
	return (3);
}

int	part_unset(t_data *info, t_input temp)
{
	int	i;
	int	posi;
	int	checker_second_error;

	checker_second_error = 0;
	posi = 0;
	i = 1;
	checker_second_error = check_second_error_unset(temp.cmd[1]);
	if (checker_second_error == 3)
	{
		error_print("minishell: unset: ", temp.cmd[1], ": invalid option\n",
			NULL);
		error_print("unset: usage: unset [-f] [-v] [-n] [name ...]\n", NULL,
			NULL, NULL);
		g_exit_status = 2;
		return (-1);
	}
	while (temp.cmd[i])
	{
		posi = check_var_exist(info, temp.cmd[i]);
		if (posi != -1)
			delete_var_from_env(info, posi);
		i++;
	}
	return (0);
}

void	run_unset(t_data *info, t_input temp)
{
	int	len_input;

	len_input = get_part_input(info, temp);
	if (len_input == 1)
		return ;
	else
	{
		if (part_unset(info, temp) == -1)
			return ;
	}
	g_exit_status = 0;
}
