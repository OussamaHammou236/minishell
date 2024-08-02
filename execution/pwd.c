/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:10:04 by iahamdan          #+#    #+#             */
/*   Updated: 2024/08/02 22:15:48 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int	check_second_error_pwd(char *str)
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

int	error_finding(t_input temp)
{
	int	checker_second_error;
	int	len_input;

	checker_second_error = 0;
	len_input = get_part_input(temp);
	if (len_input > 1)
	{
		checker_second_error = check_second_error_pwd(temp.cmd[1]);
		if (checker_second_error == 3)
		{
			error_print("minishell: pwd: ", temp.cmd[1], ": invalid option\n",
				NULL);
			error_print("pwd: usage: pwd [-LP]\n", NULL, NULL, NULL);
			ft_status(2, 0);
			return (-1);
		}
	}
	return (0);
}

void	run_pwd(t_data *info, t_input temp)
{
	char	*p;
	int		checker_second_error;

	checker_second_error = 0;
	if (error_finding(temp) == -1)
		return ;
	p = getcwd(NULL, 0);
	if (!p)
	{
		if (info->flags.store_path_currnt_dir)
			printf("%s\n", info->flags.store_path_currnt_dir);
		return ;
	}
	printf("%s\n", p);
	free(p);
	ft_status(0, 0);
}
