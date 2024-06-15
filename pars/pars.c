/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:54:06 by ohammou-          #+#    #+#             */
/*   Updated: 2024/06/15 15:07:21 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int len(char *str)
{
	t_data data;	
	data.flag = DOUBLE_Q_OFF;
	data.flag1 = SINGLE_Q_OFF;
	data.len = 0;
	data.i = 0;
	while(1)
	{
		double_single_Q(&data,str[data.i]);
		if ((data.flag1 == SINGLE_Q_ON && str[data.i] == '\'') ||  (data.flag == DOUBLE_Q_ON && str[data.i] == '"'))
			data.i++;
		if(!str[data.i])
			break ;
		if(data.flag == DOUBLE_Q_ON || data.flag1 == SINGLE_Q_ON || (str[data.i] != '"' &&  str[data.i] != '\''))
			data.len++;
		data.i++;
	}
	return data.len;
}
char *change_cmd(char *str,int len,t_data *info,t_trash **trash)
{
	t_data data;	
	data.flag = DOUBLE_Q_OFF;
	data.flag1 = SINGLE_Q_OFF;
	data.i = 0;
	data.j = len;
	data.str = malloc(len + 1);
	add_to_trash(data.str,trash);
	ft_bzero(data.str,len + 1);
	data.len = 0;
	while(str[data.i])
	{
		double_single_Q(&data,str[data.i]);
		if((data.flag == DOUBLE_Q_ON && str[data.i] != '"') || (data.flag1 == SINGLE_Q_ON && str[data.i] != '\'') || (str[data.i] != '"' &&  str[data.i] != '\''))
		{
			data.str[data.len] = str[data.i];
			data.len++;
		}
		data.i++;
	}
	return data.str;
}

void etc_change(t_input **list,t_data *info,t_data *data,t_trash **trash)
{
	int i;

	i = 0;
	while(data->cmd[data->len][i])
	{
		if((data->cmd[data->len][i] == '>' || data->cmd[data->len][i] == '<') && data->cmd[data->len + 1])
		{
			(*list)->red[data->i] = ft_strdup(data->cmd[data->len]);
			(*list)->red[data->i + 1] =  ft_strdup(data->cmd[data->len + 1]);
			add_to_trash((*list)->red[data->i],trash);
			add_to_trash((*list)->red[data->i + 1],trash);
			data->len++;
			data->i += 2;
			return ;
		}
		else
		{
			(*list)->cmd[data->j] = change_cmd(data->cmd[data->len],len(data->cmd[data->len]),info,trash);
			data->j++;
			return ;
		}
		i++;
	}
}
void change(t_input **list,t_data *info,char **cmd,t_trash **trash)
{
	int i;
	void *tmp;
	t_data data;
	data.i = 0;
	data.j = 0;
	data.len = 0;
	data.cmd = cmd;
	while(cmd[data.len])
	{
		etc_change(list,info,&data,trash);
		data.len++;
	}
}

void command(char *line,t_input **list,t_data *info,t_trash **trash)
{
	int i;
	int j;
	char **cmd;
	char **s;
	t_input *node;
	j = 0;
	cmd = ft_mini_split(line,'|',trash);
	while(cmd[j])
	{
		node = ft_lstnew(cmd);
		add_to_trash(node,trash);
		check_tocken(cmd[j],&node,1,trash);
		change(&node,info,ft_mini_split(cmd[j],' ',trash),trash);
		printf("-----------cmd---------------\n");
		for(int c = 0;node->cmd[c];c++)
			printf("[%s]\n",node->cmd[c]);
		printf("-----------reds---------------\n");
		for(int b = 0;node->red[b];b++)
		  	printf("[%s]\n",node->red[b]);
		ft_lstadd_back(list,node);
	 	j++;
	}
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
