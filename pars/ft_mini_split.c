/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:56:42 by ohammou-          #+#    #+#             */
/*   Updated: 2024/04/24 20:38:09 by ohammou-         ###   ########.fr       */
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

char **mini_split(char *str,char sp)
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
		s[i] = malloc(j);
		if(*(str + j) == '\0')
			ft_strlcpy(s[i],str,j + 1);
		else
		 	ft_strlcpy(s[i],str,j);
		printf("%s\n",s[i]);
		str += j;
		i++;
	}
	return s;
}

int main()
{
	char *s;
	char **b;
	while(1)
	{
		s = readline("mini>");
		//mini_split(s, '|');
		b = mini_split(s, '|');
		// for(int i = 0;b[i] != NULL;i++)
		// 	printf("%s\n",b[i]);
	}
	
}