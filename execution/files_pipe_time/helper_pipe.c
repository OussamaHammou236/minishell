/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:07:19 by iahamdan          #+#    #+#             */
/*   Updated: 2024/07/18 13:06:52 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	flag_of_exit_status(void)
{
	if (g_exit_status == 1)
		exit(1);
	else if (g_exit_status == 2)
		exit(2);
	else if (g_exit_status == 125)
		exit(3);
	else if (g_exit_status == 127)
		exit(4);
	else if (g_exit_status == 130)
		exit(5);
	else
		exit(0);
}

void	first_cmd(t_data *info, t_input *temp, int **fd, int *i)
{
	signal(SIGINT, signal_handler_for_childs);
	close(fd[*i][0]);
	dup2(fd[*i][1], 1);
	close(fd[*i][1]);
	if (rediction(info, *temp) == -1)
		flag_of_exit_status();
	if (!(*temp).cmd[0])
		exit(0);
	if (check_built_cmd(info, *temp) == 1)
		flag_of_exit_status();
	if (check_cmd(info, temp->cmd[0]) == 0)
	{
		if (info->flags.unset_path == 0)
			error_print("minishell: command not found: ", temp->cmd[0], "\n", NULL);
		exit(4);
	}
	execve(info->current_path, temp->cmd, info->env);
}

void	middle_cmd(t_data *info, t_input *temp, int **fd, int *i)
{
	signal(SIGINT, signal_handler_for_childs);
	close(fd[*i - 1][1]);
	dup2(fd[*i - 1][0], 0);
	close(fd[*i - 1][0]);
	if (rediction(info, *temp) == -1)
		flag_of_exit_status();
	if (!(*temp).cmd[0])
		exit(0);
	if (check_built_cmd(info, *temp) == 1)
		flag_of_exit_status();
	if (check_cmd(info, temp->cmd[0]) == 0)
	{
		if (info->flags.unset_path == 0)
			error_print("minishell: command not found: ", temp->cmd[0], "\n", NULL);
		exit(4);
	}
	execve(info->current_path, temp->cmd, info->env);
}

void	last_cmd(t_data *info, t_input *temp, int **fd, int *i)
{
	signal(SIGINT, signal_handler_for_childs);
	dup2(fd[*i - 1][0], 0);
	close(fd[*i - 1][0]);
	dup2(fd[*i][1], 1);
	close(fd[*i][1]);
	if (rediction(info, *temp) == -1)
		flag_of_exit_status();
	if (!(*temp).cmd[0])
		exit(0);
	if (check_built_cmd(info, *temp) == 1)
		flag_of_exit_status();
	if (check_cmd(info, temp->cmd[0]) == 0)
	{
		if (info->flags.unset_path == 0)
			error_print("minishell: command not found: ", temp->cmd[0], "\n", NULL);
		exit(4);
	}
	execve(info->current_path, temp->cmd, info->env);
}

int	waiting_childs(void)
{
	int	st;

	while (waitpid(-1, &st, 0) != -1)
	{
		if (st == 0)
			g_exit_status = 0;
		else if (st == 256)
			g_exit_status = 1;
		else if (st == 512)
			g_exit_status = 2;
		else if (st == 768)
			g_exit_status = 125;
		else if (st == 1024)
			g_exit_status = 127;
		else if (st == 1280 || st == 2)
			return (g_exit_status = 130, 0);
	}
	return (1);
}
