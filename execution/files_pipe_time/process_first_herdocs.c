#include "../../header.h"

static  void create_name_file(t_data *info)
{
    int     i;
    char    *str;
    char    *store;
    i = 0;
    while (i < 2147483647)
    {
        store = ft_itoa(i);
        str = ft_strjoin(".", store);
        free(store);
        if (access(str, F_OK) == -1)
        {
            info->flags.names[info->flags.number_files] = str;
            return ;
        }
        free(str);
        i++;
    }
}

static void	handle_ctrl_d_in_herdoc_sp(int fd_herdoc)
{
	close(fd_herdoc);
	exit(0);
}

static void	child_part_sp(t_data *info, t_input temp, t_trash *trash, int posi)
{
    int     fd_herdoc;
    char    *str;

	signal(SIGINT, signal_handler_for_childs);
	dup2(info->flags.fd_stdin, 0);
	dup2(info->flags.fd_stdout, 1);
	fd_herdoc = open(info->flags.names[info->flags.number_files -1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		str = readline("> ");
		if (!str)
			handle_ctrl_d_in_herdoc_sp(fd_herdoc);
		if (cmp_str(str, temp.red[posi + 1]) == 1)
		{
			free(str);
			break ;
		}
		if (temp.is_qouts[(posi) / 2] == 0)
			write(fd_herdoc, expand_str(str, &trash, info, 0),
				strlen(expand_str(str, &trash, info, 0)));
		else
			write(fd_herdoc, str,strlen(str));
		write(fd_herdoc, "\n", 1);
		free(str);
	}
	close(fd_herdoc);
	exit(0);
}

static int	herdoc_sp(t_data *info, t_input temp, t_trash *trash, int posi)
{
	int		id;
	int		st;

	id = fork();
	if (!id)
		child_part_sp(info, temp, trash, posi);
	else
	{
		wait(&st);
		if (st == 1280)
			return (-1);
	}
	return (0);
}



int    start_process(t_data *info, t_input temp, t_trash *trash)
{
    int     i;
    int     flag;

    flag = 0;
    i = 0;
    while(temp.red[i])
    {
        if (cmp_str(temp.red[i], "<<") == 1)
	    {
            if (flag == 0)
            {
                flag = 1;
                create_name_file(info);
                info->flags.number_files++;
            }
            if (herdoc_sp(info, temp, trash, i) == -1)
                return(g_exit_status = 130, -1);
	    }
        i++;
    }
    return (0);
}

int    run_herdoc_first(t_data *info)
{
    int     i;
    t_input	*temp;
    t_trash		*trash;

	trash = NULL;
    i = 0;
    temp = &info->input;
    while (i < info->number_cmd)
    {
        if (start_process(info, *temp, trash) == -1)
            return (-1);
        i++;
        temp = temp->next;
    }
    return (0);
}
