/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_status.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:52:38 by ohammou-          #+#    #+#             */
/*   Updated: 2024/08/02 19:59:19 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int ft_status(int b, int fg)
{
    static int exit;
    if (!fg)
        exit = b;
    return (exit);
}

t_data *data_global(t_data *data, int fg)
{
    static t_data *data_gl;

    if (!fg)
        data_gl = data;
    return data_gl;
}