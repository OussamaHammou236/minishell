/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_part_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 00:30:25 by iahamdan          #+#    #+#             */
/*   Updated: 2024/07/08 14:42:34 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	error_print(char *str1, char *str2, char *str3, char *str4)
{
	if (str1)
		write(2, str1, ft_strlen(str1));
	if (str2)
		write(2, str2, ft_strlen(str2));
	if (str3)
		write(2, str3, ft_strlen(str3));
	if (str4)
		write(2, str4, ft_strlen(str4));
}

int	get_len_number(int x)
{
	int	i;
	int	store;

	i = 0;
	store = 0;
	if (x == 0)
		return (1);
	store = x / 10;
	while (store != 0)
	{
		store = store / 10;
		i++;
	}
	i++;
	return (i);
}

void	shlvl_part_two(t_data *info, int posi, char *new_shlvl,
		char *my_num_in_str)
{
	int	i;

	i = 0;
	while (info->env[posi][i] != '=')
	{
		new_shlvl[i] = info->env[posi][i];
		i++;
	}
	new_shlvl[i] = info->env[posi][i];
	i++;
	while (my_num_in_str[i - 6])
	{
		new_shlvl[i] = my_num_in_str[i - 6];
		i++;
	}
	new_shlvl[i] = '\0';
}

char	*make_new_shlvl(t_data *info, int posi)
{
	int		i;
	int		my_num;
	char	*my_num_in_str;
	int		len;
	char	*new_shlvl;

	i = 0;
	my_num = 0;
	len = 0;
	while (info->env[posi][i] != '=')
		i++;
	i++;
	my_num = ft_atoi(&info->env[posi][i]);
	my_num++;
	my_num_in_str = ft_itoa(my_num);
	len = 6 + get_len_number(my_num);
	new_shlvl = malloc(sizeof(char) * len + 1);
	shlvl_part_two(info, posi, new_shlvl, my_num_in_str);
	free(my_num_in_str);
	return (new_shlvl);
}
