/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:05:45 by ohammou-          #+#    #+#             */
/*   Updated: 2024/05/09 22:07:30 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
#define MINISHELL_H

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

typedef struct s_data
{
	int flag;
	int flag1;
	int flag2;
	char *str;
	int len;
	int i;
	char **cmd;
} t_data;

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

char **ft_mini_split(char *str,char sp);
int edit_line(char *str);
char *set_spase(char *str);
void double_single_Q(t_data *data,char c);
void ft_error(char *str);
int len_of_str(char *str);
char *handel_parenthese(char *line);

#endif