/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:54:06 by ohammou-          #+#    #+#             */
/*   Updated: 2024/05/24 20:52:35 by ohammou-         ###   ########.fr       */
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
char *change_cmd(char *str,int len,t_data *info)
{
	t_data data;	
	data.flag = DOUBLE_Q_OFF;
	data.flag1 = SINGLE_Q_OFF;
	data.i = 0;
	data.j = len;
	data.str = malloc(len + 1);
	data.str[len] = '\0';
	data.len = 0;
	while(1)
	{
		if(data.flag == DOUBLE_Q_OFF && data.flag1 == SINGLE_Q_OFF && str[data.i] == '"')
		{
			data.flag = DOUBLE_Q_ON;
			data.i++;
		}
		if(data.flag == DOUBLE_Q_OFF && data.flag1 == SINGLE_Q_OFF && str[data.i] == '\'')
		{
			data.flag1 = SINGLE_Q_ON;
			data.i++;
		}
		if(str[data.i] == '$' && data.flag1 == SINGLE_Q_OFF)
		  	expande(str ,&data ,info);
		if (data.flag == DOUBLE_Q_ON && str[data.i] == '"')
			data.flag = DOUBLE_Q_OFF;
		if (data.flag1 == SINGLE_Q_ON && str[data.i] == '\'')
			data.flag1 = SINGLE_Q_OFF;
		if(str[data.i] == '\0')
			break ;
		if((data.flag == DOUBLE_Q_ON || data.flag1 == SINGLE_Q_ON || (str[data.i] != '"' &&  str[data.i] != '\'')))
		{
			data.str[data.len] = str[data.i];
			data.len++;
		}
		data.i++;
	}
	return data.str;
}

void chenge(t_input **list,t_data *info)
{
	int j;
	int i;
	void *tmp;
	t_data data;
	j = 0;
	while((*list)->cmd[j])
	{
		i = 0;
		while((*list)->cmd[j][i])
		{
			if((*list)->cmd[j][i] == '"' || (*list)->cmd[j][i] == '\'' ||(*list)->cmd[j][i] == '$' )
			{
				tmp = (*list)->cmd[j];
				(*list)->cmd[j] = change_cmd((*list)->cmd[j],len((*list)->cmd[j]),info);
				free(tmp);
				break ;
			}
			i++;
		}
		j++;
	}
}

void command(char *line,t_input **list,t_data *info)
{
	int i;
	int j;
	char **cmd;
	char **s;
	t_input *node;
	void *tmp;
	j = 0;
	cmd = ft_mini_split(line,'|');
	while(cmd[j])
	{
		node = ft_lstnew(ft_mini_split(cmd[j],' '));
		check_tocken(cmd[j],&node,1);
		chenge(&node,info);
		for(int c = 0;node->cmd[c];c++)
			printf("%s\n",node->cmd[c]);
		ft_lstadd_back(list,node);
		free(cmd[j]);
	 	j++;
	}
	free(cmd);
}

// int main(int ac,char **av)
// {
// 	t_input *node = NULL;
// 	t_data data;
// 	while(1)
// 	{
// 		char *str = readline("\033[1;36m❖ minishell\033[1;33m →$\033[0m \033[0m");
// 		add_history(str);
// 		rl_redisplay();
// 		data.str = set_spase(str);
// 		if(check_syntax_error(data) == 0 && check_tocken(data.str) == 0)
//  			command(data.str,&node);
// 		else
// 		{
// 			printf("syntax error\n");
// 			free(str);	
// 		}
// 	}
// }
