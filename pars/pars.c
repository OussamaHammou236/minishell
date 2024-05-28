/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:54:06 by ohammou-          #+#    #+#             */
/*   Updated: 2024/05/28 17:54:16 by ohammou-         ###   ########.fr       */
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

void chenge(t_input **list,t_data *info,char **cmd)
{
	int j;
	int i;
	void *tmp;
	t_data data;
	data.i = 0;
	data.j = 0;
	j = 0;
	while(cmd[j])
	{
		i = 0;
		while(cmd[j][i])
		{
			if((cmd[j][i] == '>' || cmd[j][i] == '<') && cmd[j + 1])
			{
				(*list)->red[data.i] = ft_strdup(cmd[j]);
				(*list)->red[data.i + 1] =  ft_strdup(change_cmd(cmd[j + 1],len(cmd[j + 1]),info));
				free(cmd[j]);
				j++;
				data.i += 2;
				break;
			}
			else
			{
				(*list)->cmd[data.j] = ft_strdup(change_cmd(cmd[j],len(cmd[j]),info));
				data.j++;
				break;
			}
			 i++;
		}
		free(cmd[j]);
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
		node = ft_lstnew(cmd);
		check_tocken(cmd[j],&node,1);
		chenge(&node,info,ft_mini_split(cmd[j],' '));
		// //printf("[%s]\n", node->cmd[0]);
		for(int c = 0;node->cmd[c];c++)
			printf("%s\n",node->cmd[c]);
		printf("-----------reds---------------\n");
		for(int b = 0;node->red[b];b++)
		  	printf("'%s'\n",node->red[b]);
		//ft_lstadd_back(list,node);
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
