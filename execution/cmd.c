/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:37:53 by iahamdan          #+#    #+#             */
/*   Updated: 2024/07/30 18:39:49 by ohammou-         ###   ########.fr       */
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

	change_cmd_var_env(info, cmd);
	pid = fork();
	g_data.exit_status = 0;
	signal(SIGQUIT, handler_ctrl_backslash_child);
	if (!pid)
	{
		if (execve(info->current_path, cmd, info->env) == -1)
		{
			perror("minishell");
			exit(1);
		}
	}
	else
	{
		wait(&s);
		signal(SIGQUIT, handler_ctrl_backslash);
		if (g_data.exit_status == 130)
			return ;
		g_data.exit_status = get_exit_status(s);
	}
}
