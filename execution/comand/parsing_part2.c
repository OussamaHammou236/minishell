/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:30:18 by iahamdan          #+#    #+#             */
/*   Updated: 2024/08/02 22:16:04 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	get_error(int status, char *input, t_data *info)
{
	if (status == 0)
	{
		if (info->flags.unset_path == 1 || search_for_character(input,
				'/') == 1)
			error_print("minishell: ", input, ": No such file or directory\n",
				NULL);
		else
			error_print("minishell: command not found: ", input, "\n", NULL);
		ft_status(127, 0);
	}
	else if (status == 1)
		return (1);
	else if (status == 2)
	{
		error_print("minishell: ", input, ":Is a directory\n", NULL);
		ft_status(126, 0);
	}
	else if (status == 3)
	{
		error_print("minisehll: ", input, ": Permission denied\n", NULL);
		ft_status(126, 0);
	}
	return (0);
}

int	check_built_cmd(t_data *info, t_input temp)
{
	if (cmp_str(temp.cmd[0], "cd") == 1)
	{
		if (run_cd(info, temp) == 0)
			update_env(info);
		return (1);
	}
	if (cmp_str(temp.cmd[0], "echo") == 1)
		return (run_echo(temp), 1);
	if (cmp_str(temp.cmd[0], "pwd") == 1)
		return (run_pwd(info, temp), 1);
	if (cmp_str(temp.cmd[0], "env") == 1)
		return (run_env(info, temp), 1);
	if (cmp_str(temp.cmd[0], "export") == 1)
		return (run_export(info, temp), 1);
	if (cmp_str(temp.cmd[0], "unset") == 1)
		return (run_unset(info, temp), 1);
	if (cmp_str(temp.cmd[0], "exit") == 1)
		return (run_exit(info, temp), 1);
	if (cmp_str(temp.cmd[0], "true") == 1)
		return (run_true(), 1);
	return (0);
}
