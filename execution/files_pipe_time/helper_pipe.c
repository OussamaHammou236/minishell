/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:07:19 by iahamdan          #+#    #+#             */
/*   Updated: 2024/08/06 22:42:40 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	flag_of_exit_status(void)
{
	if (ft_status(0, 1) == 1)
		exit(1);
	else if (ft_status(0, 1) == 2)
		exit(2);
	else if (ft_status(0, 1) == 125)
		exit(3);
	else if (ft_status(0, 1) == 127)
		exit(4);
	else if (ft_status(0, 1) == 130)
		exit(5);
	else if (ft_status(0, 1) == 126)
		exit(6);
	else
		exit(0);
}

void	first_cmd(t_data *info, t_input *temp, int **fd, int *i)
{
	signal(SIGINT, signal_handler_for_childs);
	signal(SIGQUIT, SIG_DFL);
	close(fd[*i][0]);
	dup2(fd[*i][1], 1);
	close(fd[*i][1]);
	if (rediction(info, *temp) == -1)
		flag_of_exit_status();
	if (!(*temp).cmd[0])
		exit(0);
	if (check_built_cmd(info, *temp) == 1)
		flag_of_exit_status();
	if (get_error(check_cmd(info, temp->cmd[0]), temp->cmd[0], info) != 1)
		flag_of_exit_status();
	if (execve(info->current_path, temp->cmd, info->env) == -1)
		exit(1);
}

void	middle_cmd(t_data *info, t_input *temp, int **fd, int *i)
{
	signal(SIGINT, signal_handler_for_childs);
	signal(SIGQUIT, SIG_DFL);
	close(fd[*i - 1][1]);
	dup2(fd[*i - 1][0], 0);
	close(fd[*i - 1][0]);
	if (rediction(info, *temp) == -1)
		flag_of_exit_status();
	if (!(*temp).cmd[0])
		exit(0);
	if (check_built_cmd(info, *temp) == 1)
		flag_of_exit_status();
	if (get_error(check_cmd(info, temp->cmd[0]), temp->cmd[0], info) != 1)
		flag_of_exit_status();
	if (execve(info->current_path, temp->cmd, info->env) == -1)
		exit(1);
}

void	last_cmd(t_data *info, t_input *temp, int **fd, int *i)
{
	signal(SIGINT, signal_handler_for_childs);
	signal(SIGQUIT, SIG_DFL);
	dup2(fd[*i - 1][0], 0);
	close(fd[*i - 1][0]);
	dup2(fd[*i][1], 1);
	close(fd[*i][1]);
	close(fd[*i][0]);
	if (rediction(info, *temp) == -1)
		flag_of_exit_status();
	if (!(*temp).cmd[0])
		exit(0);
	if (check_built_cmd(info, *temp) == 1)
		flag_of_exit_status();
	if (get_error(check_cmd(info, temp->cmd[0]), temp->cmd[0], info) != 1)
		flag_of_exit_status();
	if (execve(info->current_path, temp->cmd, info->env) == -1)
		exit(1);
}

void	waiting_childs(t_data *info)
{
	int	st;

	signal(SIGINT, another_sig_handler);
	while (waitpid(info->flags.store_pid_last_cmd, &st, 0) != -1)
	{
		if (is_exit_last_cmd(info) == 1)
			ft_status(get_exit_status(st), 0);
		else
			handle_status_pip(st);
	}
	while (waitpid(-1, &st, 0) != -1)
		;
	signal(SIGINT, handler_ctrl_c_after_readline);
}
