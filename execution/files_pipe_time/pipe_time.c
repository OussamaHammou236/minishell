/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:07:23 by iahamdan          #+#    #+#             */
/*   Updated: 2024/08/01 15:56:31 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	child(t_data *info, t_input *temp, int **fd, int *i)
{
	if (*i == 0)
		first_cmd(info, temp, fd, i);
	else if (!temp->next)
		middle_cmd(info, temp, fd, i);
	else
		last_cmd(info, temp, fd, i);
}

void	parent(t_input *temp, int **fd, int *i)
{
	if (*i == 0)
		close(fd[*i][1]);
	else if (!temp->next)
		close(fd[*i - 1][0]);
	else
	{
		close(fd[*i - 1][0]);
		close(fd[*i][1]);
	}
}

int	**allocate_fds(int size)
{
	int	i;
	int	**fd;

	fd = manage_malloc_num_two(size);
	i = 0;
	while (i < size)
	{
		fd[i] = manage_malloc_num_one(2);
		i++;
	}
	return (fd);
}

int	pipe_time_part(t_data *info, t_input *temp, int **fd)
{
	int	i;
	int	id;

	id = 0;
	i = 0;
	while (i < info->number_cmd)
	{
		if (i < info->number_cmd - 1)
			pipe(fd[i]);
		if (check_is_there_a_herdoc(*temp) == 1)
			info->flags.index++;
		id = fork();
		info->flags.store_pid_last_cmd = id;
		if (!id)
			child(info, temp, fd, &i);
		else
			parent(temp, fd, &i);
		i++;
		temp = temp->next;
	}
	waiting_childs(info);
	dellcate_fds(fd, info->number_cmd - 1);
	return (0);
}

int	pipe_time(t_data *info)
{
	t_input	*temp;
	int		**fd;
	int		i;

	if (run_herdoc_first(info) == -1)
		return (0);
	fd = allocate_fds(info->number_cmd - 1);
	temp = &info->input;
	i = 0;
	return (pipe_time_part(info, temp, fd));
}
