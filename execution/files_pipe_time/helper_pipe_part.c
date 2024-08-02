/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_pipe_part.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:23:05 by iahamdan          #+#    #+#             */
/*   Updated: 2024/07/31 16:32:47 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	dellcate_fds(int **fd, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

int	run_herdoc_first(t_data *info)
{
	int		i;
	t_input	*temp;
	t_trash	*trash;

	trash = NULL;
	i = 0;
	temp = &info->input;
	while (i < info->number_cmd)
	{
		if (start_process(info, *temp, trash) == -1)
			return (-1);
		i++;
		temp = temp->next;
	}
	return (0);
}

int	norm(t_data *info)
{
	int	fd;

	signal(SIGINT, signal_handler_for_childs);
	dup2(info->flags.fd_stdin, 0);
	dup2(info->flags.fd_stdout, 1);
	fd = open(info->flags.names[info->flags.number_files - 1],
			O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (fd);
}
