/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:27:15 by ohammou-          #+#    #+#             */
/*   Updated: 2024/05/14 21:35:43 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void in_file(char *cmd,char *file)
{
	if(access(file.F_OK) == 0)
	{
		printf("1\n");
	}
	else
		printf("2\n");
}
int main(int ac,char **av)
{
	in_file("ls",av[1]);
}