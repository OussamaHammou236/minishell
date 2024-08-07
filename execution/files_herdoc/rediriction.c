/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rediriction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:21:49 by iahamdan          #+#    #+#             */
/*   Updated: 2024/08/06 22:38:36 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	out_file(t_input temp, t_herdoc *arg)
{
	arg->posi = arg->i;
	if (arg->error_file != 1)
	{
		if (temp.red[arg->posi + 1] == NULL)
			return (-1);
		if (check_name_devs(temp.red[arg->posi + 1], 1) == 1)
			return (0);
		if (arg->our_fd_in != -1)
			close(arg->our_fd_in);
		arg->our_fd_in = open(temp.red[arg->posi + 1],
				O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (temp.red[arg->posi + 1][0] == '\0')
		{
			error_print("minishell: ", temp.red[arg->posi + 1],
				": No such file or directory\n", NULL);
			ft_status(1, 0);
			return (-1);
		}
		if (access(temp.red[arg->posi + 1], W_OK) == -1)
			return (print_error_permi(temp.red[arg->posi + 1]), -1);
	}
	return (0);
}

int	out_file_append(t_input temp, t_herdoc *arg)
{
	arg->posi = arg->i;
	if (arg->error_file != 1)
	{
		if (temp.red[arg->posi + 1] == NULL)
			return (-1);
		if (check_name_devs(temp.red[arg->posi + 1], 1) == 1)
			return (0);
		if (arg->our_fd_in != -1)
			close(arg->our_fd_in);
		arg->our_fd_in = open(temp.red[arg->posi + 1],
				O_APPEND | O_RDWR | O_CREAT, 0644);
		if (temp.red[arg->posi + 1][0] == '\0')
		{
			error_print("minishell: ", temp.red[arg->posi + 1],
				": No such file or directory\n", NULL);
			ft_status(1, 0);
			return (-1);
		}
		if (access(temp.red[arg->posi + 1], W_OK) == -1)
			return (print_error_permi(temp.red[arg->posi + 1]), -1);
	}
	return (0);
}

int	in_file(t_input temp, t_herdoc *arg)
{
	arg->posi = arg->i;
	if (temp.red[arg->posi + 1] == NULL)
		return (-1);
	if (access(temp.red[arg->posi + 1], F_OK) != 0)
	{
		if (arg->error_file != 1)
			arg->posi_error_file = arg->posi + 1;
		arg->error_file = 1;
	}
	else
	{
		if (access(temp.red[arg->posi + 1], R_OK) == -1)
			return (print_error_permi(temp.red[arg->posi + 1]), -1);
		if (check_name_devs(temp.red[arg->posi + 1], 0) == 1)
			return (0);
		if (arg->our_fd_out != -1)
			close(arg->our_fd_out);
		arg->our_fd_out = open(temp.red[arg->posi + 1], O_RDONLY, 0644);
		arg->status = 1;
	}
	return (0);
}

void	child_part(t_data *info, t_input temp, t_herdoc *arg, t_trash *trash)
{
	unlink("/var/tmp/.h");
	signal(SIGINT, signal_handler_for_childs);
	dup2(info->flags.fd_stdin, 0);
	dup2(info->flags.fd_stdout, 1);
	arg->fd_herdoc = open("/var/tmp/.h", O_CREAT | O_APPEND | O_RDWR, 0644);
	while (1)
	{
		arg->str = readline("> ");
		if (!arg->str)
			handle_ctrl_d_in_herdoc(arg);
		if (cmp_str(arg->str, temp.red[arg->posi + 1]) == 1)
		{
			free(arg->str);
			break ;
		}
		if (temp.is_qouts[(arg->i) / 2] == 0)
			write(arg->fd_herdoc, expand_str(arg->str, &trash, info, 0),
				strlen(expand_str(arg->str, &trash, info, 0)));
		else
			write(arg->fd_herdoc, arg->str, strlen(arg->str));
		write(arg->fd_herdoc, "\n", 1);
		free(arg->str);
	}
	close(arg->fd_herdoc);
	exit(0);
}

int	herdoc(t_data *info, t_input temp, t_herdoc *arg, t_trash *trash)
{
	int	id;
	int	st;

	arg->posi = arg->i;
	id = fork();
	if (!id)
		child_part(info, temp, arg, trash);
	else
	{
		wait(&st);
		if (st == 1280)
			return (-1);
		arg->status = 2;
	}
	return (0);
}
