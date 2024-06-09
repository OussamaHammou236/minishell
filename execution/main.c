#include "../header.h"

int main(int argc, char **argv, char **env)
{
    t_data info;
    t_data data;
	t_trash *trash = NULL;
	t_trash *trash1 = NULL;
    info.env = duplacte_env(env,&trash1);
    extract_path(env, &info,&trash1);
    initialization(&info);
    t_input *tm;
    while (1)
    {
        char *str = readline("minishell-> ");
		if(str[0] == '1')
		{
			free(str);
			break;
		}
        add_history(str);
        tm = NULL;
		if(str[0])
		{
        	data.str = set_spase(str);
			if(check_syntax_error(data) == 0 && !check_tocken(data.str,&tm,0,&trash))
			{
				command(data.str,&tm,&info,&trash);
				// info.input = *tm;
				// if (check_input(&info) == -1)
				// {
				// 	printf("minishell: command not found: %s\n", info.input.cmd[0]);
				// }
				// if (info.flags.dup_stdout_used == 1)
				// {
				// 	dup2(info.flags.fd_stdout, 1);
				// 	info.flags.dup_stdout_used = 0;
				// }
				// if (info.flags.dup_stdin_used == 1)
				// {
				// 	dup2(info.flags.fd_stdin, 0);
				// 	info.flags.dup_stdin_used = 0;
				// }
				// info.flags.is_builtin_cmd = 0;
			}
			else if (check_tocken(data.str,&tm,0,&trash) == 1)
				continue ;
			else
				printf("syntax error\n");
			free(data.str);
			free_trash(&trash);
		}
		free(str);
    }
	free_trash(&trash1);
            

}