/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_cd_part.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:38:41 by iahamdan          #+#    #+#             */
/*   Updated: 2024/08/02 22:16:53 by ohammou-         ###   ########.fr       */
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

int	norm_cd_one(t_data *info)
{
	if (chdir(get_home(info)) == -1)
	{
		ft_status(1, 0);
		return (-1);
	}
	ft_status(0, 0);
	return (0);
}

int	norm_cd_two(t_input temp)
{
	error_print("minishell: cd: ", temp.cmd[1], ": invalid option\n",
		"cd: usage: cd [-L|[-P [-e]] [-@]] [dir]\n");
	ft_status(2, 0);
	return (-1);
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

int	part_two_run_cd(t_data *info, t_input temp)
{
	int	checker_second_error;

	checker_second_error = check_second_error_cd(temp.cmd[1]);
	if (checker_second_error == 2)
		return (norm_cd_one(info));
	else if (checker_second_error == 3)
		return (norm_cd_two(temp));
	if (access(temp.cmd[1], X_OK) == 0)
	{
		if (chdir(temp.cmd[1]) == -1)
		{
			error_print("minishell: ", temp.cmd[0], temp.cmd[1],
				": No such file or directory\n");
			ft_status(1, 0);
			return (-1);
		}
		ft_status(0, 0);
		return (0);
	}
	else
	{
		ft_status(1, 0);
	}
	error_print("cd: no such file or directory: ", temp.cmd[1], "\n", NULL);
	return (-1);
}
