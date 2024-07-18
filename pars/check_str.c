/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 09:36:21 by ohammou-          #+#    #+#             */
/*   Updated: 2024/07/18 16:10:37 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	check_befor_dollar(t_data *info, int i)
{
	int	c;

	c = i;
	while (info->i + c > 0 && info->sm[info->i + c] != '$')
		c--;
	c--;
	while (info->i + c > 0 && info->sm[info->i + c] != '|')
	{
		if (info->sm[info->i + c] != ' ' && info->sm[info->i + c] != '|')
			return (-1);
		c--;
	}
	while (info->sm[info->i + i] && info->sm[info->i + i] != '|')
	{
		if (info->sm[info->i + i] != ' ' && info->sm[info->i + i] != '|')
			return (-1);
		i++;
	}
	return (0);
}
