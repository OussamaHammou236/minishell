/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:27:15 by ohammou-          #+#    #+#             */
/*   Updated: 2024/05/16 18:00:32 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int in_file(char **cmd,char *file,char **env,char *path)
{
	int pid;
	int fd;

	if(access(file,F_OK) == -1)
	{
		printf("minishell:  no such file or directory: %s\n",file);
		return -1;
	}
	pid = fork();
	if(pid == 0)
	{
		fd = open(file,O_RDONLY,0644);
		dup2(fd,0);
		execve(path,cmd,env);
	}
	else
		wait(&pid);
	return 0;
}

int main(int ac,char **av,char **env)
{
	char **sp = ft_mini_split("  cat  ",' ');
	in_file(sp,av[1],env,"/bin/cat");
}