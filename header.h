/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:47:50 by ohammou-          #+#    #+#             */
/*   Updated: 2024/07/08 23:39:29 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef HEADER_H
# define HEADER_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft/libft.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

extern int g_exit_status;

typedef struct s_herdoc_arg_norm
{
	int fd[2];
	int     i;
    int     posi;
    int     our_fd_in;
    int     our_fd_out;
    char    *str;
    int     status;
    int     error_file;
    int     posi_error_file;
}t_herdoc;

typedef struct s_export_norm
{
	char *new_variable;
    int len_var;
    int i;
    int len_total;
    int var;
    int var_not_containes_equal;
}s_export;


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

typedef struct s_trash
{
	void *adr;
	struct s_trash *next;	
} t_trash;

typedef struct t_data{
    char **path;
    char *current_path;
    char **env;
    int number_cmd;
	
	
	
    struct t_flags flags;
    struct s_input input;

	struct s_trash **trash;

	int	flag_free_current_path;
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
	int fg;
	int v;
	char *sm;
}t_data;

# define PIP 1
# define WORD 2
# define IN_F 3
# define OUT_F 4
# define RE_INF 5
# define RE_OUTF 6

# define DOUBLE_Q_OFF 0
# define DOUBLE_Q_ON 1
# define SINGLE_Q_OFF 0
# define SINGLE_Q_ON 1

#define RED "\033[31m"
#define BLUEB "\033[44m"
#define RST "\033[0m" 


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
void    run_exit(t_data *info, t_input temp);
int    pipe_time(t_data *info);
int check_built_cmd(t_data *info, t_input temp);
int    rediction(t_data *info, t_input temp);
void	handler_ctrl_backslash(int x);
void    update_env(t_data *info);
void    signal_handler_for_childs(int x);
void	handler_ctrl_c_in_readline(int x);
void	handler_ctrl_c_after_readline(int x);
void    free_something_after_exit(t_data *info);
int     get_exit_status(int status);
int     is_containe_equal_flag(char *user_var);
void    printf_to_stderr(char *str);
void    error_print(char *str1, char *str2, char *str3, char *str4);


char				**ft_mini_split(char *str, char sp, t_trash **trash);
int					edit_line(char *str);
char				*set_spase(char *str);
void				double_single_q(t_data *data, char c);
void				command(char *line, t_input **list, t_trash **trash);
int					check_syntax_error(t_data data);
int					check_tocken(char *str, t_input **list, int flag,
						t_trash **trash);
void				free_trash(t_trash **trash);
void				add_to_trash(void *adr, t_trash **lst);
void				free_trash(t_trash **trash);
void				add_to_trash(void *adr, t_trash **lst);
void				free_trash(t_trash **trash);
void				expande(char *str, t_data *info, t_data *data,
						t_trash **trash);
int					cont_words(char *str, char sp);
char				*expand_str(char *str, t_trash **trash, t_data *info,
						int fg);
char				*add_qoutes(char *str);
char				*ftmalloc(int len, t_trash **trash);
void				initialization_data(t_data *data, int fg);
// libft

int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
t_input	*ft_lstnew();
t_input	*ft_lstlast(t_input *lst);
void	ft_lstadd_back(t_input **lst, t_input *new);
char	*ft_itoa(int n);
void	ft_bzero(void *s, size_t n);
int	ft_atoi(const char *str);

// new 
int out_file(t_data *info, t_input temp, t_herdoc *arg);
int out_file_append(t_data *info, t_input temp, t_herdoc *arg);
int in_file(t_data *info, t_input temp, t_herdoc *arg);
int herdoc(t_data *info, t_input temp, t_herdoc *arg, t_trash *trash);
void	delete_var_from_env(t_data *info, int posi);
void    flag_of_exit_status(void);
void    first_cmd(t_data *info, t_input *temp, int **fd, int *i);
void    middle_cmd(t_data *info, t_input *temp, int **fd, int *i);
void    last_cmd(t_data *info, t_input *temp, int **fd, int *i);
int    waiting_childs(void);
char	*get_current_path(void);
char	*make_format_path(char *str);
void	update_old_pwd(t_data *info, char *str);
void	update_env(t_data *info);
void	display_exporting_var(t_data *info);
int	check_second_error_export(char *str);
int	check_correct_arg(char *str, int *sign_plus);
int	check_is_exist(char **env, char *user_var);
int	is_containe_equal_flag(char *user_var);
int	len_str_equal(char *str);
void	part_one_upd_var(s_export *arg_export, char *variable, int posi,
		t_data *info);
void	part_two_upd_var(s_export *arg_export, char *variable, int posi,
		t_data *info);
void	upd_variable(t_data *info, char *variable, int posi);
char	*ft_strdup_export(char *variable);
void	child_part(t_data *info, t_input temp, t_herdoc *arg, t_trash *trash);
void	delete_var_from_env(t_data *info, int posi);
void	shlvl_increament(t_data *info);
void	initialization(t_data *info);
int	cmp_str_env(char *str1, const char *str2, int len_str2);
int	get_part_input(t_data *info, t_input temp);
void	extract_path(char **env, t_data *info);
void	error_print(char *str1, char *str2, char *str3, char *str4);
int	get_len_number(int x);
void	shlvl_part_two(t_data *info, int posi, char *new_shlvl,
		char *my_num_in_str);
char	*make_new_shlvl(t_data *info, int posi);
void	export_operation(t_data *info, char *user_var, int sign_plus);
void	add_var_to_env(t_data *info, char *variable, int sign_plus);
void	part_add_var_to_env(t_data *info, int *i, char **upd_env, int len);
int	handle_sign_plus(t_data *info, char *variable);
char	*part_handle_sign_plus(t_data *info, char *variable);
int	check_equality_export(char *var_env, char *user_var);
void	print_error_permi(char *str, t_data *info);
// test//


// hint : 
/*
exit(0) == 0
exit(1) == 256
exit(2) == 512
exit(3) == 768
exit(4) == 1024
exit(5) == 1280
*/ // those just flags .


#endif