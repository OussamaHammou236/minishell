/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_herdoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:16:52 by ohammou-          #+#    #+#             */
/*   Updated: 2024/07/24 10:45:47 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	check_herdoc(t_data *data)
{
	if (data->nb_of_herdoc > 16)
	{
		printf("minishell: maximum here-document count exceeded \n");
		exit(2);
	}
	else if (data->tab[data->i] == RE_OUTF)
		data->nb_of_herdoc++;
}

int	red_check(char *str)
{
	int	i;

	i = 0;
	if (!*str)
		return (-1);
	while (str[i])
	{
		if (str[i] == ' ')
			return (-1);
		i++;
	}
	return (0);
}
