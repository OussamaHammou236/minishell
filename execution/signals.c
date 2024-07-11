/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:10:33 by iahamdan          #+#    #+#             */
/*   Updated: 2024/07/05 18:10:33 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	handler_ctrl_c_in_readline(int x)
{
	if (x == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	g_exit_status = 130;
}

void	handler_ctrl_c_after_readline(int x)
{
	if (x == SIGINT)
	{
		printf("\n");
	}
	g_exit_status = 130;
}

void	handler_ctrl_backslash(int x)
{
	if (x == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_handler_for_childs(int x)
{
	if (x == SIGINT)
	{
		g_exit_status = 130;
		exit(5);
	}
}
