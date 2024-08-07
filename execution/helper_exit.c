/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 00:25:18 by iahamdan          #+#    #+#             */
/*   Updated: 2024/08/06 16:44:45 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	is_negative(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-')
			return (1);
		i++;
	}
	return (0);
}

static int	cmp_str_exi(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

int	negative_side(char *our_num, char *long_min)
{
	int	store;

	store = 0;
	if (ft_strlen(our_num) > ft_strlen(long_min))
		return (free(our_num), -1);
	else if (ft_strlen(our_num) < ft_strlen(long_min))
		return (free(our_num), 1);
	else
	{
		store = cmp_str_exi(our_num, long_min);
		if (store < 0)
			return (free(our_num), 1);
		else if (store > 0)
			return (free(our_num), -1);
		else
			return (free(our_num), 1);
	}
	return (0);
}

int	positive_side(char *our_num, char *long_max)
{
	int	store;

	store = 0;
	if (ft_strlen(our_num) > ft_strlen(long_max))
		return (free(our_num), -1);
	else if (ft_strlen(our_num) < ft_strlen(long_max))
		return (free(our_num), 1);
	else
	{
		store = cmp_str_exi(our_num, long_max);
		if (store < 0)
			return (free(our_num), 1);
		else if (store > 0)
			return (free(our_num), -1);
		else
			return (free(our_num), 1);
	}
	return (0);
}

int	handle_long_max(char *str)
{
	int		is_nega;
	char	*our_num;
	char	*long_max;
	char	*long_min;

	is_nega = is_negative(str);
	our_num = skip_zero(str, is_nega);
	long_max = "9223372036854775807";
	long_min = "-9223372036854775808";
	if (is_nega == 1)
		return (negative_side(our_num, long_min));
	else
		return (positive_side(our_num, long_max));
	return (free(our_num), 0);
}
