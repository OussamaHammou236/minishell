/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:05:45 by ohammou-          #+#    #+#             */
/*   Updated: 2024/05/18 20:34:05 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
#define MINISHELL_H

#include "header.h"


# define DOUBLE_Q_OFF 0
# define DOUBLE_Q_ON 1
# define SINGLE_Q_OFF 0
# define SINGLE_Q_ON 1
# define PARENTHESE_OFF 0
# define PARENTHESE_ON 1

typedef struct s_list
{
	char **cmd;
	int type;
	struct s_list *next;	
} t_list;


typedef enum e_token
{
	PIP,
	WORD,
	IN_F,
	OUT_F,
	RE_INF,
	RE_OUTF
} t_token;


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
char *expande(char *str,int len);
#endif