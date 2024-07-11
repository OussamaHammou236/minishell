/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:37:53 by iahamdan          #+#    #+#             */
/*   Updated: 2024/07/09 20:58:41 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	handler_ctrl_backslash_child(int x)
{
	(void)x;
}

void	run_cmd(t_data *info, char **cmd)
{
	int	pid;
	int	s;

	pid = fork();
	g_exit_status = 0;
	signal(SIGQUIT, handler_ctrl_backslash_child);
	if (!pid)
		execve(info->current_path, cmd, info->env);
	else
	{
		wait(&s);
		signal(SIGQUIT, handler_ctrl_backslash);
		if (g_exit_status == 130)
			return ;
		g_exit_status = get_exit_status(s);
	}
}
