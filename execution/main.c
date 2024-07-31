/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:36:40 by iahamdan          #+#    #+#             */
/*   Updated: 2024/07/30 22:31:12 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_data	g_data;

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
	if (!data->str)
		return ;
	add_to_trash(data->str, &trash);
	if (check_syntax_error(*data) == 0 && !check_tocken(data->str, &tm, 0,
			&trash))
	{
		if (command(data->str, &tm, &trash, info) == -1)
			return ;
		info->input = *tm;
		if (check_input(info) == -1)
		{
			error_print("minishell: command not found: ", info->input.cmd[0],
				"\n", NULL);
			g_data.exit_status = 127;
			change_cmd_var_env(info, info->input.cmd);
		}
		reset_fds(info);
	}
	else
		g_data.exit_status = 2;
	info->flags.index = -1;
}

void	begining_minishell(t_data *info, t_trash **trash, char **env, int argc)
{
	*trash = NULL;
	if (argc != 1)
	{
		error_print("ERROR: Arguments are not Allowed!\n", NULL, NULL, NULL);
		exit(1);
	}
	if (!env[0])
		info->env = make_mini_env();
	else
		info->env = duplacte_env(env);
	g_data.env = info->env;
	initialization(info);
	info->trash = *trash;
	signal(SIGQUIT, handler_ctrl_backslash);
}

void	delete_files(t_data *info)
{
	int		i;

	i = 0;
	while (i < info->flags.number_files)
	{
		unlink(info->flags.names[i]);
		i++;
	}
	unlink(".herdoc_buff");
}

int	main(int argc, char **argv, char **env)
{
	t_data		info;
	t_data		data;
	t_trash		*trash;
	t_input		*tm;
	char		*str;

	g_data.exit_status = 0;
	begining_minishell(&info, &trash, env, argc);
	while (1)
	{
		signal(SIGINT, handler_ctrl_c_in_readline);
		str = readline("minishell-> ");
		signal(SIGINT, handler_ctrl_c_after_readline);
		if (!str)
		{
			free_something_after_exit(&info);
			printf("exit\n");
			exit(0);
		}
		add_history(str);
		tm = NULL;
		data.str = expand_str(str, &trash, &info, 1);
		if (data.str)
		{
			if (data.str[0])
				run_minishell(&info, trash, tm, &data);
			delete_files(&info);
			free(str);
			free_trash(&trash);
			if (info.flag_free_current_path == 1)
			{
				free(info.current_path);
				info.flag_free_current_path = 0;
			}
		}
	}
}

// pwd . when we delete the dirctory we are in . minishell will block .
// -- leaks
// check all function that can fail with NULL . 
// ././
// export tartibe . 

