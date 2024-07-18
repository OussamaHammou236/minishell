/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:36:40 by iahamdan          #+#    #+#             */
/*   Updated: 2024/07/18 14:54:45 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int		g_exit_status = 0;

void	reset_fds(t_data *info)
{
	if (info->flags.dup_stdout_used == 1)
	{
		dup2(info->flags.fd_stdout, 1);
		info->flags.dup_stdout_used = 0;
	}
	if (info->flags.dup_stdin_used == 1)
	{
		dup2(info->flags.fd_stdin, 0);
		info->flags.dup_stdin_used = 0;
	}
}

void	run_minishell(t_data *info, t_trash *trash, t_input *tm, t_data *data)
{
	data->str = set_spase(data->str);
	add_to_trash(data->str, &trash);
	if (check_syntax_error(*data) == 0 && !check_tocken(data->str, &tm, 0,
			&trash))
	{
		command(data->str, &tm, &trash);
		info->input = *tm;
		if (check_input(info) == -1)
		{
			error_print("minishell: command not found: ", info->input.cmd[0],
				"\n", NULL);
			g_exit_status = 127;
			change_cmd_var_env(info, info->input.cmd);
		}
		reset_fds(info);
	}
	else
		g_exit_status = 2;
}

void	begining_minishell(t_data *info, t_trash **trash, char **env, int argc)
{
	*trash = NULL;
	if (argc != 1)
	{
		error_print("ERROR: Arguments are not Allowed!\n", NULL, NULL, NULL);
		exit(1);
	}
	info->env = duplacte_env(env);
	extract_path(info->env, info);
	initialization(info);
	info->trash = trash;
	signal(SIGQUIT, handler_ctrl_backslash);
}

int	main(int argc, char **argv, char **env)
{
	t_data		info;
	t_data		data;
	t_trash		*trash;
	t_input		*tm;
	char		*str;

	begining_minishell(&info, &trash, env, argc);
	while (1)
	{
		signal(SIGINT, handler_ctrl_c_in_readline);
		str = readline("\033[1;36m❖ minishell\033[1;33m →$\033[0m \033[0m");
		signal(SIGINT, handler_ctrl_c_after_readline);
		if (!str)
		{
			free_something_after_exit(&info);
			exit(0);
		}
		add_history(str);
		tm = NULL;
		data.str = expand_str(str, &trash, &info, 1);
		if (data.str[0])
			run_minishell(&info, trash, tm, &data);
		unlink(".herdoc_buff");
		free(str);
		free_trash(&trash);
		if (info.flag_free_current_path == 1)
		{
			free(info.current_path);
			info.flag_free_current_path = 0;
		}
	}
}

// env , printenv problem with "$_" expand . (the solution : fake env).
// pwd . when we delete the dirctory we are in . minishell will block .
// -- leaks
// ctrl -d , you must print exit . 
// you must print exit in exit cmd . 
// check all function that can fail with NULL . 