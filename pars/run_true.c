/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_true.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:05:43 by ohammou-          #+#    #+#             */
/*   Updated: 2024/07/24 19:50:59 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../header.h"

void	run_true(void)
{
	return ;
}

char	*add_single_double_q(char *str)
{
	char	*s;
	if (ft_strchr(str, '\''))
		s = add_qoutes(str, '"');
	else
		s = add_qoutes(str, '\'');
	return s;
}