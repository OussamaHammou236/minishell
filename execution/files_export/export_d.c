/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:59:15 by iahamdan          #+#    #+#             */
/*   Updated: 2024/08/01 15:21:00 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	ft_free_storing_env(char **env)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (env[len])
		len++;
	while (i < len)
	{
		free(env[i]);
		i++;
	}
	free(env);
}

char	**delete_raw_env(char **env, int posi)
{
	int		i;
	int		j;
	int		len;
	char	**upd_env;

	i = 0;
	j = 0;
	len = 0;
	while (env[len])
		len++;
	upd_env = manage_malloc_two(len);
	while (env[i])
	{
		if (i != posi)
			upd_env[j] = ft_strdup(env[i]);
		if (i != posi)
			j++;
		i++;
	}
	upd_env[j] = NULL;
	ft_free_storing_env(env);
	return (upd_env);
}

int	is_less_that_str(char *str1, char *str2)
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
