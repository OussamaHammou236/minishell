/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:54:06 by ohammou-          #+#    #+#             */
/*   Updated: 2024/04/25 21:22:26 by ohammou-         ###   ########.fr       */
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
	cmd = ft_mini_split(line,' ');
	while(cmd[j])
	{
		//s = ft_mini_split(cmd[j],' ');
		// i = 0;
		// while(s[i])
		// {
	 	//    	printf("%s  %d\n",s[i],i);
		// 	i++;
		// }
		// for(int v = 0;s[v];v++)
		// node = ft_lstnew(ft_mini_split(cmd[j],' '));
		// ft_lstadd_back(list,node);
		printf("%s\n",cmd[j]);
		// free(cmd[j]);
		j++;
	}
	
}

int main(int ac,char **av)
{
	t_list *node = NULL;
	command(av[1],&node);
	// while(node)
	// {
	// 	for(int i = 0;node->cmd[i];i++)
	// 		printf("%s\n",node->cmd[i]);
	// 	node = node->next;
	// }
}