/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:30:29 by iahamdan          #+#    #+#             */
/*   Updated: 2024/06/27 16:02:32 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_number(const char *s, int sign)
{
	int		my_number;

	my_number = 0;
	while (*s >= '0' && *s <= '9')
	{
		my_number = my_number * 10 + (*s - 48);
		s++;
	}
	my_number *= sign;
	return (my_number);
}

int	ft_atoi(const char *str)
{
	const char		*s;
	int				sign;

	s = str;
	sign = 1;
	while (*s == 32 || *s == '\t' || *s == '\v'
		|| *s == '\n' || *s == '\r' || *s == '\f')
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign *= -1;
		s++;
	}
	if (*s >= '0' && *s <= '9')
		return (get_number(s, sign));
	return (0);
}
