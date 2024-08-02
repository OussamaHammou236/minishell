/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:07:19 by iahamdan          #+#    #+#             */
/*   Updated: 2024/08/02 22:13:04 by ohammou-         ###   ########.fr       */
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
	if (check_cmd(info, temp->cmd[0]) == 0)
	{
		if (info->flags.unset_path == 0)
			error_print("minishell: command not found: ", temp->cmd[0], "\n",
				NULL);
		exit(4);
	}
	execve(info->current_path, temp->cmd, info->env);
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
	if (check_cmd(info, temp->cmd[0]) == 0)
	{
		if (info->flags.unset_path == 0)
			error_print("minishell: command not found: ", temp->cmd[0], "\n",
				NULL);
		exit(4);
	}
	execve(info->current_path, temp->cmd, info->env);
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
	if (check_cmd(info, temp->cmd[0]) == 0)
	{
		if (info->flags.unset_path == 0)
			error_print("minishell: command not found: ", temp->cmd[0], "\n",
				NULL);
		exit(4);
	}
	execve(info->current_path, temp->cmd, info->env);
}

void	waiting_childs(t_data *info)
{
	int	st;

	signal(SIGINT, another_sig_handler);
	while (waitpid(info->flags.store_pid_last_cmd, &st, 0) != -1)
	{
		if (st == 0)
			ft_status(0, 0);
		else if (st == 256)
			ft_status(1, 0);
		else if (st == 512)
			ft_status(2, 0);
		else if (st == 768)
			ft_status(125, 0);
		else if (st == 1024)
			ft_status(127, 0);
		else if (st == 1280 || st == 2)
			ft_status(130, 0);
	}
	while (waitpid(-1, &st, 0) != -1)
		;
	signal(SIGINT, handler_ctrl_c_after_readline);
}
