/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:37:53 by iahamdan          #+#    #+#             */
/*   Updated: 2024/08/03 16:35:40 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	handle_status(int s)
{
	if (s == 131)
	{
		write(2, "Quit (core dumped)\n", 19);
		ft_status(131, 0);
		return (1);
	}
	if (ft_status(0, 1) == 130)
	{
		if (s == 2)
			write(2, "\n", 1);
		else
			return (0);
		return (1);
	}
	return (0);
}

void	run_cmd(t_data *info, char **cmd)
{
	int	pid;
	int	s;

	change_cmd_var_env(info, cmd);
	pid = fork();
	ft_status(0, 0);
	if (!pid)
	{
		signal(SIGQUIT, SIG_DFL);
		if (execve(info->current_path, cmd, info->env) == -1)
			exit(1);
	}
	else
	{
		wait(&s);
		if (handle_status(s) == 1)
			return ;
		ft_status(get_exit_status(s), 0);
	}
}
