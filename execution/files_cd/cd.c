/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:23:29 by iahamdan          #+#    #+#             */
/*   Updated: 2024/07/09 20:59:30 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

char	*get_home(t_data *info)
{
	int	i;

	i = 0;
	while (info->env[i])
	{
		if (cmp_str_env(info->env[i], "HOME=", 5) == 1)
		{
			return (&info->env[i][5]);
			break ;
		}
		i++;
	}
	return (NULL);
}

static int	check_second_error_cd(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (str[0] != '-')
		return (0);
	if (i == 2)
		if (str[1] == '-')
			return (2);
	return (3);
}

void	part_two_run_cd(t_data *info, t_input temp)
{
	int	checker_second_error;

	checker_second_error = check_second_error_cd(temp.cmd[1]);
	if (checker_second_error == 2)
	{
		chdir(get_home(info));
		g_exit_status = 0;
		return ;
	}
	else if (checker_second_error == 3)
	{
		error_print("minishell: cd: ", temp.cmd[1], ": invalid option\n",
			"cd: usage: cd [-L|[-P [-e]] [-@]] [dir]\n");
		g_exit_status = 2;
		return ;
	}
	if (access(temp.cmd[1], X_OK) == 0)
	{
		chdir(temp.cmd[1]);
		g_exit_status = 0;
		return ;
	}
	else
		g_exit_status = 1;
	error_print("cd: no such file or directory: ", temp.cmd[1], "\n", NULL);
}

int	check_specifique_case(t_data *info, t_input temp)
{
	int		i;

	i = 0;
	while (temp.cmd[1][i])
	{
		if (temp.cmd[1][i] != 126)
			return (0);
		i++;
	}
	return (1);
}

void	run_cd(t_data *info, t_input temp)
{
	int	len_input;

	len_input = get_part_input(info, temp);
	if (len_input == 1)
	{
		chdir(get_home(info));
		g_exit_status = 0;
		return ;
	}
	if (len_input == 2)
	{
		if (check_specifique_case(info, temp) == 1)
		{
			chdir(get_home(info));
			g_exit_status = 0;
			return ;
		}
		part_two_run_cd(info, temp);
	}
	else
	{
		error_print("minishell: cd: too many arguments\n", NULL, NULL, NULL);
		g_exit_status = 1;
	}
}
