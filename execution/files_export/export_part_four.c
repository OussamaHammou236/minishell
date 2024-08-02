/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_part_four.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:26:26 by iahamdan          #+#    #+#             */
/*   Updated: 2024/08/01 15:51:14 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

char	*part_handle_sign_plus(char *variable)
{
	char	*new_var;
	int		len;
	int		i;
	int		j;

	j = 0;
	i = 0;
	len = len_str_equal(variable);
	new_var = manage_malloc_one(len);
	while (i < len - 1)
	{
		if (variable[i] == '+')
			j++;
		new_var[i] = variable[j];
		i++;
		j++;
	}
	new_var[len - 1] = '\0';
	return (new_var);
}

int	handle_sign_plus(t_data *info, char *variable)
{
	char	*new_var;
	int		i;

	new_var = part_handle_sign_plus(variable);
	i = 0;
	while (info->env[i])
	{
		if (check_equality_export(info->env[i], new_var) == 0)
		{
			upd_variable(info, variable, i);
			free(new_var);
			return (0);
		}
		i++;
	}
	free(new_var);
	return (1);
}

void	part_add_var_to_env(t_data *info, int *i, char **upd_env, int len)
{
	while (info->env[*i])
	{
		upd_env[*i] = ft_strdup(info->env[*i]);
		if (len > 2)
		{
			if (!info->env[*i + 2])
				break ;
		}
		*i = *i + 1;
	}
}

void	add_var_to_env(t_data *info, char *variable, int sign_plus)
{
	int		i;
	int		len;
	char	**upd_env;

	i = 0;
	len = 0;
	if (sign_plus == 1)
	{
		if (handle_sign_plus(info, variable) == 0)
			return ;
	}
	while (info->env[len])
		len++;
	upd_env = manage_malloc_two(len + 2);
	part_add_var_to_env(info, &i, upd_env, len);
	if (sign_plus == 1)
		upd_env[++i] = ft_strdup_export(variable);
	else
		upd_env[++i] = ft_strdup(variable);
	upd_env[i + 1] = ft_strdup(info->env[i]);
	upd_env[i + 2] = NULL;
	ft_free_env(info, len);
	info->env = upd_env;
}

void	export_operation(t_data *info, char *user_var, int sign_plus)
{
	int	check_existance;

	check_existance = check_is_exist(info->env, user_var);
	if (check_existance != -1)
	{
		if (is_containe_equal_flag(user_var) == 1)
			return ;
		else
		{
			free(info->env[check_existance]);
			info->env[check_existance] = ft_strdup(user_var);
			return ;
		}
	}
	else
		add_var_to_env(info, user_var, sign_plus);
}
