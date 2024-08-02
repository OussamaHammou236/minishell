/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:37:36 by iahamdan          #+#    #+#             */
/*   Updated: 2024/08/01 15:38:13 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	*manage_malloc_one(int size)
{
	char	*your_block;

	your_block = malloc(sizeof(char) * size);
	if (!your_block)
		exit(1);
	return (your_block);
}

char	**manage_malloc_two(int size)
{
	char	**your_block;

	your_block = malloc(sizeof(char *) * size);
	if (!your_block)
		exit(1);
	return (your_block);
}

int	*manage_malloc_num_one(int size)
{
	int	*your_block;

	your_block = malloc(sizeof(int) * size);
	if (!your_block)
		exit(1);
	return (your_block);
}

int	**manage_malloc_num_two(int size)
{
	int	**your_block;

	your_block = malloc(sizeof(int *) * size);
	if (!your_block)
		exit(1);
	return (your_block);
}
