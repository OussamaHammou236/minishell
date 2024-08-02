/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_exit_part.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:44:51 by iahamdan          #+#    #+#             */
/*   Updated: 2024/08/01 14:44:51 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	*skip_zero(char *str, int is_negative)
{
	int	i;

	i = 0;
	if (is_negative == 1)
	{
		i++;
		while (str[i])
		{
			if (str[i] != '0')
				return (ft_strjoin("-", &str[i]));
			i++;
		}
		return (ft_strdup(str));
	}
	while (str[i])
	{
		if (str[i] != '0')
			return (ft_strdup(&str[i]));
		i++;
	}
	return (ft_strdup(str));
}
