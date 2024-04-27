/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:56:42 by ohammou-          #+#    #+#             */
/*   Updated: 2024/04/27 16:49:11 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
# define DOUBLE_Q_OFF 1
# define DOUBLE_Q_ON 2
# define SINGLE_Q_OFF 3
# define SINGLE_Q_ON 4

// ls | 'vd' | echo " ffff | s"
int cont_words(char *str,char sp)
{
	int i;
	int j;
	int flag;

	i = 0;
	j = 0;
	flag = DOUBLE_Q_OFF;
	int flag2 = SINGLE_Q_OFF;
	while(str[i])
	{
		if(str[i] && str[i] != sp)
		{
			if(flag == DOUBLE_Q_OFF && flag2 == SINGLE_Q_OFF)
				j++;
			while(str[i] && str[i] != sp)
			{
				if( flag == DOUBLE_Q_OFF && str[i] == '"')
				{
					flag = DOUBLE_Q_ON;
					i++;
				}
				if(flag == DOUBLE_Q_ON && str[i] == '"')
					flag = DOUBLE_Q_OFF;

				if(flag2 == SINGLE_Q_OFF && str[i] == 39)
				{
					flag2 = SINGLE_Q_ON;
					i++;
				}
				if(flag2 == SINGLE_Q_ON && str[i] == 39)
					flag2 = SINGLE_Q_OFF;
				i++;
			}
		}
		else
			i++;
	}
	if(flag2 == SINGLE_Q_ON || flag == DOUBLE_Q_ON)
	{
		printf("error\n");
		exit(1);
	}
		
	return j;
}

int len_of_words(char *str,char sp)
{
	int i;
	int flag;
	int flag2;
	i = 0;
	flag = DOUBLE_Q_OFF;
	flag2 = SINGLE_Q_OFF;
	while(str[i])
	{
		if(flag == DOUBLE_Q_OFF && str[i] == '"')
		{
			flag = DOUBLE_Q_ON;
			i++;
		}
		if(flag == DOUBLE_Q_ON && str[i] == '"')
			flag = DOUBLE_Q_OFF;
		if(flag2 == SINGLE_Q_OFF && str[i] == 39)
		{
			flag2 = SINGLE_Q_ON;
			i++;
		}
		if(flag2 == SINGLE_Q_ON && str[i] == 39)
			flag2 = SINGLE_Q_OFF;
		if(flag == DOUBLE_Q_OFF && flag2 == SINGLE_Q_OFF && str[i] == sp)
			return i + 1;
		i++;
		
	}
	return i;
}

char **ft_mini_split(char *str,char sp)
{
	int len;
	int j;
	char **s;
	int i;
	int flag = 0;

	i = 0;
	len = cont_words(str,sp);
	//printf("%d\n",len);
	s = malloc((len + 1) * sizeof(char *));
	s[len] = NULL;
	while(i < len && *str)
	{
		while(*str && *str == sp)
			str++;
		j = len_of_words(str,sp);
		if(*(str + j - 1) != sp)
		{
			s[i] = malloc(j + 1);
			ft_strlcpy(s[i],str,j + 1);
		}
		else
		{
			s[i] = malloc(j);
		 	ft_strlcpy(s[i],str,j);
		}
		str += j;
		i++;
	}
	return s;
}



