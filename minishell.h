/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:05:45 by ohammou-          #+#    #+#             */
/*   Updated: 2024/05/20 18:53:23 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
#define MINISHELL_H

#include "header.h"


# define DOUBLE_Q_OFF 0
# define DOUBLE_Q_ON 1
# define SINGLE_Q_OFF 0
# define SINGLE_Q_ON 1


typedef struct s_list
{
	char **cmd;
	int type;
	struct s_list *next;	
} t_list;


# define PIP 1
# define WORD 2
# define IN_F 3
# define OUT_F 4
# define RE_INF 5
# define RE_OUTF 6


#include "libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <fcntl.h>

char **ft_mini_split(char *str,char sp);
int edit_line(char *str);
char *set_spase(char *str);
void double_single_Q(t_data *data,char c);
int cont_words(char *str,char sp);
char *set_spase(char *str);
int check_tocken(char *str,t_input **list,int flag);
int check_syntax_error(t_data data);
void expande(char *str,t_data *info);
#endif