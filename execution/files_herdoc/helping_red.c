/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helping_red.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:07:49 by iahamdan          #+#    #+#             */
/*   Updated: 2024/08/06 22:40:16 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	last_open_part_one(t_input temp, t_herdoc *arg)
{
	error_print("minishell: ", temp.red[arg->posi_error_file],
		": No such file or directory\n", NULL);
	ft_status(1, 0);
	return (-1);
}

void	last_open_part_two(t_data *info, t_herdoc *arg)
{
	if (info->number_cmd == 1)
		arg->fd_herdoc = open("/var/tmp/.h", O_RDWR, 0644);
	else
	{
		arg->fd_herdoc = open(info->flags.names[info->flags.index], O_RDWR,
				0644);
	}
	dup2(arg->fd_herdoc, 0);
	close(arg->fd_herdoc);
	info->flags.dup_stdin_used = 1;
}

int	last_oper(t_data *info, t_input temp, t_herdoc *arg)
{
	if (arg->error_file == 1)
		return (last_open_part_one(temp, arg));
	if (arg->status == 1)
	{
		dup2(arg->our_fd_out, 0);
		info->flags.dup_stdin_used = 1;
	}
	else if (arg->status == 2)
		last_open_part_two(info, arg);
	if (arg->our_fd_in != -1)
	{
		dup2(arg->our_fd_in, 1);
		close(arg->our_fd_in);
		info->flags.dup_stdout_used = 1;
	}
	return (0);
}

int	check_name_devs(char *str, int flag)
{
	if (flag == 1)
	{
		if (cmp_str(str, "/dev/stdout") == 1)
			return (1);
		if (cmp_str(str, "/proc/self/fd/1") == 1)
			return (1);
	}
	else if (flag == 0)
	{
		if (cmp_str(str, "/dev/stdin") == 1)
			return (1);
		if (cmp_str(str, "/proc/self/fd/0") == 1)
			return (1);
	}
	return (0);
}
