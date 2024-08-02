/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:10:33 by iahamdan          #+#    #+#             */
/*   Updated: 2024/08/02 22:15:56 by ohammou-         ###   ########.fr       */
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
	ft_status(130, 0);
}

void	handler_ctrl_c_after_readline(int x)
{
	if (x == SIGINT)
	{
		ft_status(130, 0);
	}
}

void	signal_handler_for_childs(int x)
{
	if (x == SIGINT)
	{
		ft_status(130, 0);
		printf("\n");
		exit(5);
	}
}

void	another_sig_handler(int x)
{
	(void)x;
	printf("\n");
}
