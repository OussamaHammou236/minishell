/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:50:12 by iahamdan          #+#    #+#             */
/*   Updated: 2024/07/18 10:39:08 by iahamdan         ###   ########.fr       */
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
	new_path = malloc(sizeof(char) * len_new_path);
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

int	check_cmd(t_data *info, char *input)
{
	int	i;

	i = 0;
	if (input[0] == '\0')
		return (0);
	if (access(input, X_OK) == 0)
	{
		info->current_path = input;
		info->flag_free_current_path = 0;
		return (1);
	}
	if (check_path(info, input) == 1)
		return (0);
	while (info->path[i])
	{
		info->current_path = make_path(info->path[i], input);
		if (access(info->current_path, X_OK) == 0)
			return (info->flag_free_current_path = 1, 1);
		free(info->current_path);
		i++;
	}
	return (0);
}

int	check_built_cmd(t_data *info, t_input temp)
{
	if (cmp_str(temp.cmd[0], "cd") == 1)
		return (run_cd(info, temp), update_env(info), 1);
	if (cmp_str(temp.cmd[0], "echo") == 1)
		return (run_echo(info, temp), 1);
	if (cmp_str(temp.cmd[0], "pwd") == 1)
		return (run_pwd(info, temp), 1);
	if (cmp_str(temp.cmd[0], "env") == 1)
	{
		if (check_path(info, temp.cmd[0]) == 1)
			return (1);
		return (run_env(info, temp), 1);
	}
	if (cmp_str(temp.cmd[0], "export") == 1)
		return (run_export(info, temp), 1);
	if (cmp_str(temp.cmd[0], "unset") == 1)
		return (run_unset(info, temp), 1);
	if (cmp_str(temp.cmd[0], "exit") == 1)
		return (run_exit(info, temp), 1);
	return (0);
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
		else if (check_cmd(info, info->input.cmd[0]) == 1)
			run_cmd(info, info->input.cmd);
		else
		{
			if (info->flags.unset_path == 1)
				return (0);
			return (-1);
		}
	}
	else
		return (pipe_time(info));
	return (0);
}
