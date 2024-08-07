/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:50:12 by iahamdan          #+#    #+#             */
/*   Updated: 2024/08/06 22:31:03 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

char	*make_path(char *path, char *input)
{
	int		len_new_path;
	char	*new_path;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len_new_path = ft_strlen(path) + ft_strlen(input) + 2;
	new_path = manage_malloc_one(len_new_path);
	while (path[i])
	{
		new_path[i] = path[i];
		i++;
	}
	new_path[i++] = '/';
	while (input[j])
	{
		new_path[i] = input[j++];
		i++;
	}
	new_path[i] = '\0';
	return (new_path);
}

int	check_cmd_part(t_data *info, char *input)
{
	int	i;

	i = 0;
	while (info->path[i])
	{
		info->current_path = make_path(info->path[i], input);
		if (access(info->current_path, F_OK) == 0)
		{
			if (access(info->current_path, X_OK) == -1)
				return (ft_free_path(info), info->flag_free_current_path = 1,
					3);
			return (ft_free_path(info), info->flag_free_current_path = 1, 1);
		}
		free(info->current_path);
		i++;
	}
	return (0);
}

int	check_cmd(t_data *info, char *input)
{
	int	store;

	if (input[0] == '\0' || cmp_str(input, "..") == 1)
		return (0);
	if (cmp_str(input, ".") == 1)
		return (4);
	if (check_if_is_dir(input, info) == 1)
		return (2);
	if (search_for_character(input, '/') == 1 && access(input, F_OK) == 0)
	{
		if (access(input, X_OK) == -1)
			return (3);
		info->current_path = input;
		info->flag_free_current_path = 0;
		return (1);
	}
	extract_path(info->env, info);
	if (info->path == NULL)
		return (0);
	store = check_cmd_part(info, input);
	if (store == 3)
		return (3);
	else if (store == 1)
		return (1);
	return (ft_free_path(info), 0);
}

int	get_number_cmd(t_data *info)
{
	int		len;
	t_input	*temp;

	len = 0;
	temp = &info->input;
	while (temp)
	{
		temp = temp->next;
		len++;
	}
	return (len);
}

int	check_input(t_data *info)
{
	info->number_cmd = get_number_cmd(info);
	if (info->number_cmd == 1)
	{
		if (info->input.red[0])
		{
			if (rediction(info, info->input) == -1)
				return (0);
		}
		if (!info->input.cmd[0])
			return (0);
		if (check_built_cmd(info, info->input) == 1)
			change_cmd_var_env(info, info->input.cmd);
		else
		{
			if (get_error(check_cmd(info, info->input.cmd[0]),
					info->input.cmd[0], info) == 1)
				run_cmd(info, info->input.cmd);
		}
	}
	else
		return (pipe_time(info));
	return (0);
}
