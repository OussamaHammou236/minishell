/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:06:26 by ohammou-          #+#    #+#             */
/*   Updated: 2024/04/21 15:28:57 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void check(char *str,char **sp,char **cmd,char **env)
{
	char *line;
	int i = 0;
	int acc;
	int pid = fork();
	if (pid < 0)
		return ;
	if (!pid)
	{
		while(sp[i])
		{
			line = ft_strjoin(sp[i],"/");
			line = ft_strjoin(line,cmd[0]);
			acc = access(line,X_OK);
			if(acc == 0)
				execve(line,cmd,env);
			free(line);
			i++;
		}
		if(acc == -1)
			printf("bash: %s: command not found\n",cmd[0]);
	}
	else
		wait(NULL);
}

char *ft_env(char **env)
{
	int j = 0;
	
	while(env[j])
	{
		if(env[j][0] == 'P' && env[j][3] == 'H')
			return &env[j][5];
		else
			j++;
	}
	return NULL;
}

void pars(char **env, char *line)
{
	// char **sp;
	// int i;
	// int j;

	// i = 0;
	// j = 0;
	// sp = ft_split(line,' ');

	// while(sp[j])
	// {
		
	// }
	
}

int main(int ac, char **av, char **env)
{
	char *line;
	char **sp;
	ac = 0;
	
	sp = ft_split(ft_env(env),':');
	int pid = fork();
	if (pid < 0)
		return 1;
	if(pid == 0)
	{
		while(1)
		{
			
			line = readline("minishell> ");
			char **cmd = ft_split(line,' ');
			check(line, sp,cmd,env);
			free(line);
		}
		
	}
	else
	{
		wait(NULL);
		return 0;
	}
}

