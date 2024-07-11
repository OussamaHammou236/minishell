/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_part_three.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:24:44 by iahamdan          #+#    #+#             */
/*   Updated: 2024/07/06 14:26:20 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	len_str_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
	{
		i++;
	}
	return (i + 1);
}

void	part_one_upd_var(s_export *arg_export, char *variable, int posi,
		t_data *info)
{
	arg_export->i = 0;
	arg_export->len_var = 0;
	arg_export->var_not_containes_equal = 0;
	while (variable[arg_export->i] != '=')
		arg_export->i++;
	arg_export->i++;
	while (variable[arg_export->i])
	{
		arg_export->i++;
		arg_export->len_var++;
	}
	if (is_containe_equal_flag(info->env[posi]) == 1)
		arg_export->var_not_containes_equal = 1;
	arg_export->len_total = arg_export->len_var + ft_strlen(info->env[posi]) + 1
		+ arg_export->var_not_containes_equal;
	arg_export->new_variable = malloc(sizeof(char) * arg_export->len_total);
	arg_export->i = 0;
	arg_export->var = ft_strlen(variable) - arg_export->len_var;
}

void	part_two_upd_var(s_export *arg_export, char *variable, int posi,
		t_data *info)
{
	while (arg_export->i < arg_export->len_total)
	{
		if (info->env[posi][arg_export->i])
			arg_export->new_variable[arg_export->i] = info->env[posi]
			[arg_export->i];
		else
		{
			if (arg_export->var_not_containes_equal == 1)
			{
				arg_export->new_variable[arg_export->i] = '=';
				arg_export->i++;
			}
			break ;
		}
		arg_export->i++;
	}
}

void	upd_variable(t_data *info, char *variable, int posi)
{
	s_export	arg_export;

	part_one_upd_var(&arg_export, variable, posi, info);
	part_two_upd_var(&arg_export, variable, posi, info);
	while (arg_export.i < arg_export.len_total)
	{
		if (variable[arg_export.var])
		{
			arg_export.new_variable[arg_export.i] = variable[arg_export.var];
			arg_export.var++;
		}
		else
			arg_export.new_variable[arg_export.i] = '\0';
		arg_export.i++;
	}
	free(info->env[posi]);
	info->env[posi] = arg_export.new_variable;
}

char	*ft_strdup_export(char *variable)
{
	int		len;
	char	*new_var;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_var = malloc(len);
	len = ft_strlen(variable);
	while (i < len)
	{
		if (variable[i] == '+')
			j++;
		new_var[i] = variable[j];
		i++;
		j++;
	}
	return (new_var);
}
