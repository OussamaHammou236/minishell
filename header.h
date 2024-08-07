/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:47:50 by ohammou-          #+#    #+#             */
/*   Updated: 2024/08/06 22:43:15 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_herdoc_arg_norm
{
	int				fd[2];
	int				fd_herdoc;
	int				i;
	int				posi;
	int				our_fd_in;
	int				our_fd_out;
	char			*str;
	int				status;
	int				error_file;
	int				posi_error_file;
}					t_herdoc;

typedef struct s_export_norm
{
	char			*new_variable;
	int				len_var;
	int				i;
	int				len_total;
	int				var;
	int				var_not_containes_equal;
}					t_export;

struct				s_flags
{
	int				fd_stdout;
	int				fd_stdin;

	int				dup_stdout_used;
	int				dup_stdin_used;

	int				unset_path;

	char			*names[16];
	int				number_files;
	int				index;

	char			*store_path_currnt_dir;

	int				store_pid_last_cmd;
};

typedef struct s_trash
{
	void			*adr;
	struct s_trash	*next;
}					t_trash;

typedef struct s_data
{
	char			**path;
	char			*current_path;
	char			**env;
	int				number_cmd;

	struct s_flags	flags;
	struct s_input	input;

	struct s_trash	*trash;

	int				flag_free_current_path;
	int				flag;
	int				flag1;
	int				flag2;
	char			*str;
	int				len;
	int				i;
	char			**cmd;
	int				*tab;
	int				j;
	char			*src;
	char			*s;
	int				f;
	int				nb;
	int				fg;
	int				v;
	char			*sm;
	int				nb_of_herdoc;
	int				n;
	int				exit_status;
	int				check;

}					t_data;

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

# define RED "\033[31m"
# define BLUEB "\033[44m"
# define RST "\033[0m"

int					ft_status(int b, int fg);
char				*edit_str(char *str, t_trash **trash);
int					cmp_str_env(char *str1, const char *str2, int len_str2);
void				extract_path(char **env, t_data *info);
char				*make_path(char *path, char *input);
int					check_cmd(t_data *info, char *input);
int					check_input(t_data *info);
void				run_cmd(t_data *info, char **cmd);
void				initialization(t_data *info);
int					run_cd(t_data *info, t_input temp);
int					get_part_input(t_input input);
char				*get_home(t_data *info);
int					cmp_str(char *str1, char *str2);
void				run_echo(t_input temp);
void				run_pwd(t_data *info, t_input temp);
void				run_env(t_data *info, t_input temp);
char				**duplacte_env(char **env);
char				*ft_strdup(const char *src);
void				run_export(t_data *info, t_input temp);
void				ft_free_env(t_data *info, int len);
void				run_unset(t_data *info, t_input temp);
void				run_exit(t_data *info, t_input temp);
int					pipe_time(t_data *info);
int					check_built_cmd(t_data *info, t_input temp);
int					rediction(t_data *info, t_input temp);
void				handler_ctrl_backslash(int x);
void				update_env(t_data *info);
void				signal_handler_for_childs(int x);
void				handler_ctrl_c_in_readline(int x);
void				handler_ctrl_c_after_readline(int x);
void				free_something_after_exit(t_data *info);
int					get_exit_status(int status);
int					is_containe_equal_flag(char *user_var);
void				printf_to_stderr(char *str);
void				error_print(char *str1, char *str2, char *str3, char *str4);
void				free_env_new(t_data *info);
char				**ft_mini_split(char *str, char sp, t_trash **trash);
int					edit_line(char *str);
char				*set_spase(char *str);
void				double_single_q(t_data *data, char c);
int					command(char *line, t_input **list, t_trash **trash,
						t_data *info);
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
char				*add_qoutes(char *str, char c);
char				*ftmalloc(int len, t_trash **trash);
void				initialization_data(t_data *data, int fg);
int					check_befor_dollar(t_data *info, int i);
void				check_herdoc(t_data *data, t_trash **trash);
int					is_white_space(char c);
char				*change_cmd(char *str, int len, t_trash **trash);
void				check_imbg(t_input **list, t_data *data, t_trash **trash,
						t_data *info);
void				run_true(void);
int					red_check(char *str);
char				*add_single_double_q(char *str);
int					len(char *str);
int					cont_words_spaces(char *str);
int					set_value(t_data *data, t_data *info, int i,
						t_trash **trash);
t_data				*data_global(t_data *data, int fg);
// new
int					out_file(t_input temp, t_herdoc *arg);
int					out_file_append(t_input temp, t_herdoc *arg);
int					in_file(t_input temp, t_herdoc *arg);
int					herdoc(t_data *info, t_input temp, t_herdoc *arg,
						t_trash *trash);
void				delete_var_from_env(t_data *info, int posi);
void				flag_of_exit_status(void);
void				first_cmd(t_data *info, t_input *temp, int **fd, int *i);
void				middle_cmd(t_data *info, t_input *temp, int **fd, int *i);
void				last_cmd(t_data *info, t_input *temp, int **fd, int *i);
void				waiting_childs(t_data *info);
char				*get_current_path(void);
char				*make_format_path(char *str);
void				update_old_pwd(t_data *info, char *str);
void				update_env(t_data *info);
void				display_exporting_var(t_data *info);
int					check_second_error_export(char *str);
int					check_correct_arg(char *str, int *sign_plus);
int					check_is_exist(char **env, char *user_var);
int					is_containe_equal_flag(char *user_var);
int					len_str_equal(char *str);
void				part_one_upd_var(t_export *arg_export, char *variable,
						int posi, t_data *info);
void				part_two_upd_var(t_export *arg_export, int posi,
						t_data *info);
void				upd_variable(t_data *info, char *variable, int posi);
char				*ft_strdup_export(char *variable);
void				child_part(t_data *info, t_input temp, t_herdoc *arg,
						t_trash *trash);
void				delete_var_from_env(t_data *info, int posi);
void				shlvl_increament(t_data *info);
void				initialization(t_data *info);
int					cmp_str_env(char *str1, const char *str2, int len_str2);
void				error_print(char *str1, char *str2, char *str3, char *str4);
int					get_len_number(int x);
void				shlvl_part_two(t_data *info, int posi, char *new_shlvl,
						char *my_num_in_str);
char				*make_new_shlvl(t_data *info, int posi);
void				export_operation(t_data *info, char *user_var,
						int sign_plus);
void				add_var_to_env(t_data *info, char *variable, int sign_plus);
void				part_add_var_to_env(t_data *info, int *i, char **upd_env,
						int len);
int					handle_sign_plus(t_data *info, char *variable);
char				*part_handle_sign_plus(char *variable);
int					check_equality_export(char *var_env, char *user_var);
void				print_error_permi(char *str);
int					check_path(t_data *info, char *input);
void				change_cmd_var_env(t_data *info, char **cmd);
void				handle_ctrl_d_in_herdoc(t_herdoc *arg);
void				export_operation(t_data *info, char *user_var,
						int sign_plus);
char				**make_mini_env(void);
void				ft_free_path(t_data *info);
int					run_herdoc_first(t_data *info);
int					check_is_there_a_herdoc(t_input temp);
void				display_exporting_var(t_data *info);
int					check_if_is_dir(char *input, t_data *info);
int					search_for_character(char *str, char c);
int					get_error(int status, char *input, t_data *info);
void				delete_files(t_data *info);
int					check_built_cmd(t_data *info, t_input temp);
char				*get_home(t_data *info);
int					part_two_run_cd(t_data *info, t_input temp);
int					is_less_that_str(char *str1, char *str2);
char				**delete_raw_env(char **env, int posi);
void				ft_free_storing_env(char **env);
int					last_oper(t_data *info, t_input temp, t_herdoc *arg);
void				dellcate_fds(int **fd, int size);
int					run_herdoc_first(t_data *info);
int					start_process(t_data *info, t_input temp, t_trash *trash);
int					norm(t_data *info);
void				another_sig_handler(int x);
int					handle_long_max(char *str);
char				*skip_zero(char *str, int is_negative);
char				*manage_malloc_one(int size);
char				**manage_malloc_two(int size);
int					*manage_malloc_num_one(int size);
int					**manage_malloc_num_two(int size);
void				norm_mai(t_data *info);
int					check_name_devs(char *str, int flag);
int					is_exit_last_cmd(t_data *info);
void				handle_status_pip(int st);
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