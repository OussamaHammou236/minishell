/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:06:49 by iahamdan          #+#    #+#             */
/*   Updated: 2024/07/06 14:06:50 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	delete_var_from_env(t_data *info, int posi)
{
	int		i;
	int		j;
	int		len;
	char	**upd_env;

	i = 0;
	j = 0;
	len = 0;
	while (info->env[len])
		len++;
	upd_env = malloc(sizeof(char *) * len);
	while (info->env[i])
	{
		if (i != posi)
			upd_env[j] = ft_strdup(info->env[i]);
		if (i != posi)
			j++;
		i++;
	}
	upd_env[j] = NULL;
	ft_free_env(info, len);
	info->env = upd_env;
}
