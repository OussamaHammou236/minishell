/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:18:18 by ohammou-          #+#    #+#             */
/*   Updated: 2024/05/15 20:18:42 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void out_file(char **cmd,char *file,char **env,char *path)
{
	int fd;
	int pid;

	fd = open(file, O_CREAT  | O_RDWR | O_TRUNC,0644);
	pid = fork();
	if(pid == 0)
	{
		dup2(fd,1);
		execve(path,cmd,env);
	}
	else
		wait(&pid);
	close(fd);
}
int main(int ac,char **av,char **env)
{
	char **sp = ft_mini_split("  ls  ",' ');
	out_file(sp,av[1],env,"/bin/ls");
}
