/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:47:50 by ohammou-          #+#    #+#             */
/*   Updated: 2024/06/04 21:07:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef HEADER_H
# define HEADER_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>


struct t_flags
{
    int is_builtin_cmd; 

	int fd_stdout;
	int fd_stdin;

	int	dup_stdout_used;
	int dup_stdin_used;

};

typedef struct s_input
{
	char **cmd;
	char **red;
	int *type;
	struct s_input *next;	
} t_input;
//ls > out > akdk > kckck >> dcc
typedef struct s_trash
{
	void *adr;
	struct s_trash *next;	
} t_trash;

typedef struct t_data{
    char **path;
    char *current_path;
    char **env;
    // char **input;
    int number_cmd;
    struct t_flags flags;
    struct s_input input;


	int flag;
	int flag1;
	int flag2;
	char *str;
	int len;
	int i;
	char **cmd;
	int *tab;
	int j;
	char *src;
	char *s;
	int f;
	int nb;
}t_data;

# define PIP 1
# define WORD 2
# define IN_F 3
# define OUT_F 4
# define RE_INF 5
# define RE_OUTF 6


size_t	ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
int     cmp_str_env(char *str1, const char *str2, int len_str2);
void    extract_path(char **env, t_data *info);
char    *make_path(char *path, char *input);
int check_cmd(t_data *info, char *input);
int     check_input(t_data *info);
void    run_cmd(t_data *info, char **cmd);
void    initialization(t_data *info);
void    run_cd(t_data *info, t_input temp);
int get_part_input(t_data *info, t_input input);
char *get_home(t_data *info);
int cmp_str(char *str1, char *str2);
void    run_echo(t_data *info, t_input temp);
void    run_pwd(t_data *info, t_input temp);
void    run_env(t_data *info, t_input temp);
char **duplacte_env(char **env);
char	*ft_strdup(const char *src);
void    run_export(t_data *info, t_input temp);
void    ft_free_env(t_data *info, int len);
void    run_unset(t_data *info, t_input temp);
void    run_exit();
int    pipe_time(t_data *info);
int check_built_cmd(t_data *info, t_input temp);
int    rediction(t_data *info, t_input temp);


char **ft_mini_split(char *str,char sp);
int edit_line(char *str);
char *set_spase(char *str);
void double_single_Q(t_data *data,char c);
void command(char *line,t_input **list,t_data *info);
int check_syntax_error(t_data data);
int check_tocken(char *str,t_input **list,int flag);
#endif