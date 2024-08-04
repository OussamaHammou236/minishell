/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_status.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:52:38 by ohammou-          #+#    #+#             */
/*   Updated: 2024/08/03 22:22:27 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	ft_status(int b, int fg)
{
	static int	exit;

	if (!fg)
		exit = b;
	return (exit);
}

t_data	*data_global(t_data *data, int fg)
{
	static t_data	*data_gl;

	if (!fg)
		data_gl = data;
	return (data_gl);
}
