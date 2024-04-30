/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:54:06 by ohammou-          #+#    #+#             */
/*   Updated: 2024/04/30 14:15:09 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *copy(char *src,int len)
{
	char *str;
	int i;
	int flag;
	int j = 0;
	i = 0;
	flag = DOUBLE_Q_OFF;
	str = malloc(len + 1);
	while(src[i])
	{
		if (flag == DOUBLE_Q_OFF && src[i] == '"')
		{
			flag = DOUBLE_Q_ON;
			i++;
		}
		if (flag == DOUBLE_Q_ON && src[i] == '"')
			flag = DOUBLE_Q_OFF;
		if(flag == DOUBLE_Q_ON)
		{
			str[j] = src[i];
			j++;
		}
		i++;
	}
	return str;
}

void len_of_word(t_list **node)
{
	int len;
	int i;
	int j = 0;
	int flag = DOUBLE_Q_OFF;
	char *str;
	void *tmp;
	
	while((*node)->cmd[j])
	{
		i = 0;
		len = 0;
		while((*node)->cmd[j][i])
		{
			if (flag == DOUBLE_Q_OFF && (*node)->cmd[j][i] == '"')
				flag = DOUBLE_Q_ON;
			else if (flag == DOUBLE_Q_ON && (*node)->cmd[j][i] == '"')
				flag = DOUBLE_Q_OFF;
			if(flag == DOUBLE_Q_ON)
				len++;
			i++;
		}
		if (len != 0)
		{
			tmp = (*node)->cmd[j];
			(*node)->cmd[j] = copy((*node)->cmd[j],len);
			free(tmp);
		}
		j++;
	}
}

void command(char *line,t_list **list)
{
	int i;
	int j;
	char **cmd;
	char **s;
	t_list *node;

	j = 0;
	cmd = ft_mini_split(line,'|');
	while(cmd[j])
	{
		node = ft_lstnew(ft_mini_split(cmd[j],' '));
		len_of_word(&node);
		ft_lstadd_back(list,node);
		free(cmd[j]);
	 	j++;
	}
	free(cmd);
	while(*list)
	{
		printf("------------------------\n");
	 	for(int i = 0;(*list)->cmd[i];i++)
	 		printf("%s\n",(*list)->cmd[i]);
	 	(*list) = (*list)->next;
	}
}

int main(int ac,char **av)
{
	t_list *node = NULL;
	while(1)
	{
		char *str = readline("\033[1;36m❖ minishell\033[1;33m →$\033[0m \033[0m");
		char **sp = ft_mini_split(str,'|');
		// for(int i = 0;sp[i];i++)
		// 	printf("|%s|\n",sp[i]);
 		command(str,&node);
	}
}