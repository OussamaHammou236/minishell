/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:17:57 by iahamdan          #+#    #+#             */
/*   Updated: 2024/08/02 22:17:23 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	print_error_permi(char *str)
{
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": Permission denied", 19);
	write(2, "\n", 1);
	ft_status(1, 0);
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

int	run_redi_part(t_data *info, t_input temp, t_herdoc *arg, t_trash *trash)
{
	if (info->number_cmd == 1)
	{
		if (herdoc(info, temp, arg, trash) == -1)
			return (-1);
	}
	else
	{
		arg->status = 2;
		arg->posi = arg->i;
	}
	return (0);
}

int	run_redi(t_data *info, t_input temp, t_herdoc *arg, t_trash *trash)
{
	if (cmp_str(temp.red[arg->i], ">") == 1)
	{
		if (out_file(temp, arg) == -1)
			return (-1);
	}
	else if (cmp_str(temp.red[arg->i], ">>") == 1)
	{
		if (out_file_append(temp, arg) == -1)
			return (-1);
	}
	else if (cmp_str(temp.red[arg->i], "<") == 1)
	{
		if (in_file(temp, arg) == -1)
			return (-1);
	}
	else if (cmp_str(temp.red[arg->i], "<<") == 1)
	{
		if (run_redi_part(info, temp, arg, trash) == -1)
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
