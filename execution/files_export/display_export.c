/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:58:46 by iahamdan          #+#    #+#             */
/*   Updated: 2024/08/01 15:20:56 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	display_var_exporting(char *str)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	printf("declare -x ");
	while (str[i])
	{
		printf("%c", str[i]);
		if (flag == 0 && str[i] == '=')
		{
			printf("\"");
			flag = 1;
		}
		i++;
	}
	if (flag == 1)
		printf("\"");
	printf("\n");
}

void	sort_exprot(t_data *info, char **store_env)
{
	int		i;
	char	*store_str;
	int		posi;
	int		j;

	posi = 0;
	j = 0;
	while (info->env[j + 1])
	{
		i = 0;
		store_str = store_env[i];
		while (store_env[i + 1])
		{
			if (is_less_that_str(store_env[i], store_str) <= 0)
			{
				store_str = store_env[i];
				posi = i;
			}
			i++;
		}
		display_var_exporting(store_str);
		store_env = delete_raw_env(store_env, posi);
		j++;
	}
	ft_free_storing_env(store_env);
}

char	**make_copy_env(t_data *info)
{
	int		i;
	int		len;
	char	**store_env;

	len = 0;
	i = 0;
	while (info->env[i])
		i++;
	len = i;
	store_env = manage_malloc_two(len + 1);
	i = 0;
	while (i < len)
	{
		store_env[i] = ft_strdup(info->env[i]);
		i++;
	}
	store_env[len] = NULL;
	return (store_env);
}

void	display_exporting_var(t_data *info)
{
	char	**store_env;

	store_env = make_copy_env(info);
	sort_exprot(info, store_env);
}
