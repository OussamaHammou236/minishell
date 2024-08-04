/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainc_part.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:03:09 by iahamdan          #+#    #+#             */
/*   Updated: 2024/08/03 22:17:43 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	norm_mai(t_data *info)
{
	info->flags.number_files = 0;
	signal(SIGINT, handler_ctrl_c_in_readline);
	data_global(info, 0);
}
