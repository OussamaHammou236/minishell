/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:56:42 by ohammou-          #+#    #+#             */
/*   Updated: 2024/04/25 21:26:08 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int cont_words(char *str,char sp)
{
	int i;
	int j;
	int flag;

	i = 0;
	j = 0;
	flag = 0;
	while(str[i])
	{
		if(str[i] && str[i] != sp)
		{
			if(flag == 0)
				j++;
			while(str[i] && str[i] != sp)
			{
				if(flag == 0 && str[i] == '"')
				{
					flag = 1;
					i++;
				}
				if(flag == 1 && str[i] == '"')
					flag = 0;
				i++;
			}
		}
		else
			i++;
	}
	return j;
}

int len_of_words(char *str,char sp)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	while(str[i])
	{
		if(flag == 0 && str[i] == '"')
		{
			flag = 1;
			i++;
		}
		if(flag == 1 && str[i] == '"')
			flag = 0;
		if(flag == 0 && str[i] == sp)
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

	i = 0;
	len = cont_words(str,sp);
	s = malloc(len * sizeof(char *));
	s[len] = NULL;
	while(*str)
	{
		j = len_of_words(str,sp);
		//printf("%d\n",j);
		s[i] = malloc(j);
		if(*(str + j - 1) != sp)
			ft_strlcpy(s[i],str,j + 1);
		else
		 	ft_strlcpy(s[i],str,j);
		str += j;
		i++;
	}
	return s;
}
