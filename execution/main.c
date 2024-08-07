/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:36:40 by iahamdan          #+#    #+#             */
/*   Updated: 2024/08/06 22:46:48 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

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
		if (command(data->str, &tm, &trash, info) == -1)
			return ;
		info->input = *tm;
		if (check_input(info) == -1)
			change_cmd_var_env(info, info->input.cmd);
		reset_fds(info);
	}
	else
		ft_status(2, 0);
	info->flags.index = -1;
}

void	begining_minishell(t_data *info, t_trash **trash, char **env, int argc)
{
	*trash = NULL;
	ft_status(0, 0);
	if (argc != 1)
	{
		error_print("ERROR: Arguments are not Allowed!\n", NULL, NULL, NULL);
		exit(1);
	}
	if (!env[0])
		info->env = make_mini_env();
	else
		info->env = duplacte_env(env);
	initialization(info);
	data_global(info, 0);
	info->trash = *trash;
	signal(SIGQUIT, SIG_IGN);
}

void	in_the_last(char *str, t_data *info, t_trash **trash, char **argv)
{
	(void)argv;
	delete_files(info);
	free(str);
	free_trash(trash);
	if (info->flag_free_current_path == 1)
	{
		free(info->current_path);
		info->flag_free_current_path = 0;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	info;
	t_data	data;
	t_trash	*trash;
	t_input	*tm;
	char	*str;

	begining_minishell(&info, &trash, env, argc);
	while (1)
	{
		norm_mai(&info);
		str = readline("minishell-> ");
		signal(SIGINT, handler_ctrl_c_after_readline);
		if (!str)
		{
			free_something_after_exit(&info);
			printf("exit\n");
			exit(WEXITSTATUS(ft_status(0, 1) * 256));
		}
		add_history(str);
		tm = NULL;
		data.str = expand_str(str, &trash, &info, 1);
		if (data.str && data.str[0])
			run_minishell(&info, trash, tm, &data);
		in_the_last(str, &info, &trash, argv);
	}
}
