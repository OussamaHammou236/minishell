#include "header.h"

int main(int argc, char **argv, char **env)
{
    t_data info;
    t_data data;
    info.env = duplacte_env(env);
    extract_path(env, &info);
    initialization(&info);
    t_input *tm;
    while (1)
    {
        char *str = readline("minishell-> ");
        add_history(str);
        data.str = set_spase(str);
        tm = NULL;
       	if(check_syntax_error(data) == 0 && !check_tocken(data.str,&tm,0))
		{
			command(data.str,&tm);
			info.input = *tm;
			if (check_input(&info) == -1)
			{
				printf("minishell: command not found: %s\n", info.input.cmd[0]);
			}
			info.flags.is_builtin_cmd = 0;
		}
		else
			printf("syntax error\n");
		free(str);
    }

            

}