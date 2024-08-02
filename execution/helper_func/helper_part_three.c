/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_part_three.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:43:23 by iahamdan          #+#    #+#             */
/*   Updated: 2024/08/01 16:42:40 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

char	*make_pwd(void)
{
	char	*p;
	char	*pwd;
	size_t	i;

	p = getcwd(NULL, 0);
	if (!p)
		return (NULL);
	pwd = manage_malloc_one(ft_strlen(p) + 5);
	pwd[0] = 'P';
	pwd[1] = 'W';
	pwd[2] = 'D';
	pwd[3] = '=';
	i = 4;
	while (i < ft_strlen(p) + 4)
	{
		pwd[i] = p[i - 4];
		i++;
	}
	pwd[i] = '\0';
	free(p);
	return (pwd);
}

char	*make_shlvl(void)
{
	char	*shlvl;

	shlvl = manage_malloc_one(8);
	shlvl[0] = 'S';
	shlvl[1] = 'H';
	shlvl[2] = 'L';
	shlvl[3] = 'V';
	shlvl[4] = 'L';
	shlvl[5] = '=';
	shlvl[6] = '1';
	shlvl[7] = '\0';
	return (shlvl);
}

char	*make_last(void)
{
	char	*last;

	last = manage_malloc_one(4);
	last[0] = '_';
	last[1] = '=';
	last[2] = ']';
	last[3] = '\0';
	return (last);
}

char	**make_mini_env(void)
{
	char	**new_env;

	new_env = manage_malloc_two(4);
	new_env[0] = make_pwd();
	new_env[1] = make_shlvl();
	new_env[2] = make_last();
	new_env[3] = NULL;
	return (new_env);
}

int	check_is_there_a_herdoc(t_input temp)
{
	int	i;

	i = 0;
	while (temp.red[i])
	{
		if (cmp_str(temp.red[i], "<<") == 1)
		{
			return (1);
		}
		i++;
	}
	return (0);
}
