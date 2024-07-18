/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:17:57 by iahamdan          #+#    #+#             */
/*   Updated: 2024/07/16 23:34:52 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	print_error_permi(char *str, t_data *info)
{
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": Permission denied", 19);
	write(2, "\n", 1);
	g_exit_status = 1;
}

void	intialization_norm_var(t_herdoc *arg)
{
	arg->posi = -1;
	arg->i = -1;
	arg->error_file = 0;
	arg->posi_error_file = -1;
	arg->our_fd_in = -1;
	arg->our_fd_out = -1;
	arg->status = 0;
}

int	last_oper(t_data *info, t_input temp, t_herdoc *arg)
{
	if (arg->error_file == 1)
	{
		error_print("minishell: ", temp.red[arg->posi_error_file],
			": No such file or directory\n", NULL);
		g_exit_status = 1;
		return (-1);
	}
	if (arg->status == 1)
	{
		dup2(arg->our_fd_out, 0);
		info->flags.dup_stdin_used = 1;
	}
	else if (arg->status == 2)
	{
		arg->fd_herdoc = open(".herdoc_buff", O_RDWR, 0644);
		dup2(arg->fd_herdoc, 0);
		close(arg->fd_herdoc);
		info->flags.dup_stdin_used = 1;
	}
	if (arg->our_fd_in != -1)
	{
		dup2(arg->our_fd_in, 1);
		close(arg->our_fd_in);
		info->flags.dup_stdout_used = 1;
	}
	return (0);
}

int	run_redi(t_data *info, t_input temp, t_herdoc *arg, t_trash *trash)
{
	if (cmp_str(temp.red[arg->i], ">") == 1)
	{
		if (out_file(info, temp, arg) == -1)
			return (-1);
	}
	else if (cmp_str(temp.red[arg->i], ">>") == 1)
	{
		if (out_file_append(info, temp, arg) == -1)
			return (-1);
	}
	else if (cmp_str(temp.red[arg->i], "<") == 1)
	{
		if (in_file(info, temp, arg) == -1)
			return (-1);
	}
	else if (cmp_str(temp.red[arg->i], "<<") == 1)
	{
		if (herdoc(info, temp, arg, trash) == -1)
			return (-1);
	}
	return (0);
}

int	rediction(t_data *info, t_input temp)
{
	t_herdoc	arg;
	t_trash		*trash;

	trash = NULL;
	intialization_norm_var(&arg);
	while (temp.red[++arg.i])
	{
		if (run_redi(info, temp, &arg, trash) == -1)
			return (-1);
	}
	if (arg.posi == -1)
		return (0);
	else if (last_oper(info, temp, &arg) == -1)
		return (-1);
	return (0);
}
