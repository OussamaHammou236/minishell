/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:56:42 by ohammou-          #+#    #+#             */
/*   Updated: 2024/04/25 22:50:07 by ohammou-         ###   ########.fr       */
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
	s = malloc((len + 1) * sizeof(char *));
	while(*str && *str == sp)
	 	str++;
	while(i < len && *str)
	{
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
	s[len] = NULL;
	return s;
}



