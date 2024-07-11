/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 00:24:19 by iahamdan          #+#    #+#             */
/*   Updated: 2024/07/06 18:03:23 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	cmp_str(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1 || !str2)
		return (0);
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}

char	**duplacte_env(char **env)
{
	int		i;
	char	**our_env;

	i = 0;
	while (env[i])
		i++;
	our_env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		our_env[i] = ft_strdup(env[i]);
		i++;
	}
	our_env[i] = NULL;
	return (our_env);
}

int	get_exit_status(int status)
{
	return (status / 256);
}
