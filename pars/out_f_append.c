/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:25:23 by ohammou-          #+#    #+#             */
/*   Updated: 2024/05/15 16:28:37 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void append(char **cmd,char *file,char **env,char *path)
{
	int fd;
	int pid;

	fd = open(file, O_CREAT  | O_RDWR | O_APPEND,0644);
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

