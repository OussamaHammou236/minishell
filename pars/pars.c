/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:54:06 by ohammou-          #+#    #+#             */
/*   Updated: 2024/04/26 14:56:18 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		ft_lstadd_back(list,node);
		free(cmd[j]);
	 	j++;
	}
	free(cmd);
	while(*list)
	{
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
		char *str = readline("minishell> ");
 		command(str,&node);
	}
}