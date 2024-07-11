/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:07:23 by iahamdan          #+#    #+#             */
/*   Updated: 2024/07/08 23:52:41 by iahamdan         ###   ########.fr       */
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

void	parent(t_data *info, t_input *temp, int **fd, int *i)
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

	fd = malloc(sizeof(int *) * size);
	i = 0;
	while (i < size)
	{
		fd[i] = malloc(sizeof(int) * 2);
		i++;
	}
	return (fd);
}

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

int	pipe_time(t_data *info)
{
	t_input	*temp;
	int		**fd;
	int		i;
	int		id;

	fd = allocate_fds(info->number_cmd - 1);
	temp = &info->input;
	i = 0;
	while (i < info->number_cmd)
	{
		if (i < info->number_cmd - 1)
			pipe(fd[i]);
		id = fork();
		if (!id)
			child(info, temp, fd, &i);
		else
			parent(info, temp, fd, &i);
		i++;
		temp = temp->next;
	}
	if (waiting_childs() == 0)
		return (dellcate_fds(fd, info->number_cmd - 1), 0);
	dellcate_fds(fd, info->number_cmd - 1);
	return (0);
}
