/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:37:27 by iahamdan          #+#    #+#             */
/*   Updated: 2024/07/08 23:14:04 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	check_equality_export(char *var_env, char *user_var)
{
	int	i;

	i = 0;
	while (var_env[i] != '\0' && var_env[i] != '=')
	{
		if (var_env[i] != user_var[i])
			return (1);
		i++;
	}
	if (var_env[i] == '=' && user_var[i] != '\0')
	{
		if (var_env[i] != user_var[i])
			return (1);
	}
	else if (user_var[i] != '\0' && user_var[i] != '=')
		return (1);
	return (0);
}

int	part_two_export(t_data *info, t_input temp)
{
	int	checker_second_error;

	checker_second_error = check_second_error_export(temp.cmd[1]);
	if (checker_second_error == 2)
	{
		display_exporting_var(info);
		g_exit_status = 0;
		return (1);
	}
	else if (checker_second_error == 3)
	{
		error_print("minishell: export: ", temp.cmd[1], ": invalid option\n",
			"export: usage: export [-fn] [name[=value] ...] or export -p\n");
		g_exit_status = 2;
		return (1);
	}
	return (0);
}

void	part_three_export(t_data *info, t_input temp, int *error_occurs)
{
	int	i;
	int	checker;
	int	sign_plus;

	checker = 0;
	sign_plus = 0;
	i = 1;
	while (temp.cmd[i])
	{
		checker = check_correct_arg(temp.cmd[i], &sign_plus);
		if (checker == -1)
		{
			error_print("minishell: export: '", temp.cmd[i],
				"': not a valid identifier\n", NULL);
			g_exit_status = 1;
			*error_occurs = 1;
		}
		else
			export_operation(info, temp.cmd[i], sign_plus);
		i++;
	}
}

void	run_export(t_data *info, t_input temp)
{
	int	len_input;
	int	error_occurs;

	error_occurs = 0;
	len_input = get_part_input(info, temp);
	if (len_input == 1)
		display_exporting_var(info);
	else
	{
		if (part_two_export(info, temp) == 1)
			return ;
		part_three_export(info, temp, &error_occurs);
	}
	if (error_occurs == 0)
		g_exit_status = 0;
}
