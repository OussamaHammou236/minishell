/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:00:48 by ohammou-          #+#    #+#             */
/*   Updated: 2024/05/16 10:08:29 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void herdoc(char *end,char **cmd,char *path,char **env)
{
	int pid;
	char *str;

	pid = fork();
	if(pid == 0)
	{
		str = get_next_line(0);
		if(!str)
			return ;
	}
	else
		wait(&pid);
}