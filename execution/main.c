#include "../header.h"

int	g_exit_status = 0;

int main(int argc, char **argv, char **env)
{
    t_data info;
    t_data data;
	t_trash *trash = NULL;
	// t_trash *trash1 = NULL;
	if(argc != 1)
	{
		printf("ERROR: Arguments are not Allowed!\n");
		exit(1);
	}
    info.env = duplacte_env(env);
    extract_path(env, &info);
    initialization(&info);
    t_input *tm;
	//---------------//
	info.trash = &trash;
	//------------//
	// -signals- //
	signal(SIGINT, handler_ctrl_c_in_readline);
	signal(SIGQUIT, handler_ctrl_backslash);
	// --- // 
    while (1)
    {
		// -signals- //
		signal(SIGINT, handler_ctrl_c_in_readline);
		// -- //
        char *str = readline("\033[1;36m❖ minishell\033[1;33m →$\033[0m \033[0m");
		// -signals- //
		signal(SIGINT, handler_ctrl_c_after_readline);
		// -- //
		if (!str) // ctrl-D
		{
			free_something_after_exit(&info);
			exit(0);
		}
		if (str[0])
        	add_history(str);
		else
			g_exit_status = 0;
        tm = NULL;
		data.str = set_spase(str);
		add_to_trash(data.str,&trash);
		if(check_syntax_error(data) == 0 && !check_tocken(data.str,&tm,0,&trash))
		{
			data.str = expand_str(data.str, &trash, &info, 0);
			if(data.str[0])
			{
				command(data.str,&tm,&trash);	
				info.input = *tm;
				if (check_input(&info) == -1)
				{
					write(2, "minishell: command not found: ", 30);
					write(2, info.input.cmd[0], ft_strlen(info.input.cmd[0]));
					write(2, "\n", 1);
					g_exit_status = 127;
				}
				if (info.flags.dup_stdout_used == 1)
				{
					dup2(info.flags.fd_stdout, 1);
					info.flags.dup_stdout_used = 0;
				}
				if (info.flags.dup_stdin_used == 1)
				{
					dup2(info.flags.fd_stdin, 0);
					info.flags.dup_stdin_used = 0;
				}
				info.flags.is_builtin_cmd = 0;
			}
		}
		else
			g_exit_status = 2;
		free(str);
		free_trash(&trash);
    }
}

// -- those two error is dosent matter ! . 
//--------------------------------------------------------------------- 
// 1
// syntax error of the "--eq" error , we must print just the first character ! . "e". 
// just run in bash : env -eqw and see the display error and compare it with yours .  

//--------------------------------------------------------------------- 

// 2
// grep fd | wc -l << q , 
// you need to handle it.
// cat | ls


// 5
// leaks .

// 6
// norminette . 

