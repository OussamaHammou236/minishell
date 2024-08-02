/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_part_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:01:45 by iahamdan          #+#    #+#             */
/*   Updated: 2024/07/30 17:08:39 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	check_second_error_export(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (str[0] != '-')
		return (0);
	if (i == 2)
		if (str[1] == '-')
			return (2);
	return (3);
}

int	check_correct_arg(char *str, int *sign_plus)
{
	int	i;

	i = 0;
	if (str[i] >= '0' && str[i] <= '9')
		return (-1);
	while (str[i] && str[i] != '=')
	{
		if (str[i + 1] == '=')
		{
			if (str[i] == '+' && i != 0)
				*sign_plus = 1;
		}
		if (*sign_plus == 0)
		{
			if ((str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z')
				&& (str[i] < '0' || str[i] > '9'))
				return (-1);
		}
		i++;
	}
	if (i == 0)
		return (-1);
	return (1);
}

int	check_is_exist(char **env, char *user_var)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (check_equality_export(env[i], user_var) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	is_containe_equal_flag(char *user_var)
{
	int	i;

	i = 0;
	while (user_var[i])
	{
		if (user_var[i] == '=')
			return (0);
		i++;
	}
	return (1);
}
