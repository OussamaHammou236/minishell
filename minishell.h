/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:05:45 by ohammou-          #+#    #+#             */
/*   Updated: 2024/04/27 22:48:42 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
#define MINISHELL_H

# define DOUBLE_Q_OFF 1
# define DOUBLE_Q_ON 2
# define SINGLE_Q_OFF 3
# define SINGLE_Q_ON 4

typedef struct s_list
{
	char **cmd;	
	int type;
	struct s_list *next;	
} t_list;

#include "libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

char **ft_mini_split(char *str,char sp);



#endif