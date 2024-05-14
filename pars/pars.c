/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:54:06 by ohammou-          #+#    #+#             */
/*   Updated: 2024/05/14 16:44:18 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int len(char *str)
{
	t_data data;	
	data.flag = DOUBLE_Q_OFF;
	data.flag1 = SINGLE_Q_OFF;
	data.len = 0;
	data.i = 0;
	while(str[data.i])
	{
		double_single_Q(&data,str[data.i]);
		if ((data.flag1 == SINGLE_Q_ON && str[data.i] == '\'') ||  (data.flag == DOUBLE_Q_ON && str[data.i] == '"'))
			data.i++;
		if(data.flag == DOUBLE_Q_ON || data.flag1 == SINGLE_Q_ON || (str[data.i] != '"' &&  str[data.i] != '\''))
			data.len++;
		data.i++;
	}
	return data.len;
}
char *change_cmd(char *str,int len)
{
	char *cmd;
	int i;
	int flag,flag1,d;
	flag = DOUBLE_Q_OFF;
	flag1 = SINGLE_Q_OFF;
	i = 0;
	cmd = malloc(len + 1);
	printf("%d\n",len);
	cmd[len] = '\0';
	d = 0;
	while(str[i])
	{
		if(flag == DOUBLE_Q_OFF && flag1 == SINGLE_Q_OFF && str[i] == '"')
		{
			flag = DOUBLE_Q_ON;
			i++;
		}
		if (flag == DOUBLE_Q_ON && str[i] == '"')
			flag = DOUBLE_Q_OFF;
		if(flag == DOUBLE_Q_OFF && flag1 == SINGLE_Q_OFF && str[i] == '\'')
		{
			flag1 = SINGLE_Q_ON;
			i++;
		}
		if (flag1 == SINGLE_Q_ON && str[i] == '\'')
			flag1 = SINGLE_Q_OFF;
		if(flag == DOUBLE_Q_ON || flag1 == SINGLE_Q_ON || (str[i] != '"' &&  str[i] != '\''))
		{
			cmd[d] = str[i];
			d++;
		}
		i++;
	}
	return cmd;
}

void chenge(t_list **list)
{
	int j;
	int i;
	void *tmp;
	j = 0;
	while((*list)->cmd[j])
	{
		i = 0;
		while((*list)->cmd[j][i])
		{
			if((*list)->cmd[j][i] == '"' || (*list)->cmd[j][i] == '\'')
			{
				tmp = (*list)->cmd[j];
				(*list)->cmd[j] = change_cmd((*list)->cmd[j],len((*list)->cmd[j]));
				free(tmp);
				break ;
			}
			i++;
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
	void *tmp;
	j = 0;
	cmd = ft_mini_split(line,'|');
	while(cmd[j])
	{
		node = ft_lstnew(ft_mini_split(cmd[j],' '));
		chenge(&node);
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
	t_data data;
	while(1)
	{
		char *str = readline("\033[1;36m❖ minishell\033[1;33m →$\033[0m \033[0m");
		add_history(str);
		rl_redisplay();
		data.str = set_spase(str);
		if(check_syntax_error(data) == 0 && check_tocken(data.str) == 0)
 			command(data.str,&node);
		else
		{
			printf("syntax error\n");
			free(str);	
		}
	}
}
