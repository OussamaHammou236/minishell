/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_true.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:05:43 by ohammou-          #+#    #+#             */
/*   Updated: 2024/07/31 15:08:06 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	run_true(void)
{
	return ;
}

char	*add_single_double_q(char *str)
{
	char	*s;

	if (!str)
		return (NULL);
	if (ft_strchr(str, '\''))
		s = add_qoutes(str, '"');
	else
		s = add_qoutes(str, '\'');
	return (s);
}

int	cont_words_spaces(char *str)
{
	t_data	data;

	data.i = 0;
	data.j = 0;
	while (str[data.i])
	{
		if (!is_white_space(str[data.i]))
		{
			data.j++;
			while (str[data.i] && !is_white_space(str[data.i]))
				data.i++;
		}
		else
			data.i++;
	}
	return (data.j);
}

int	is_white_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

char	*ftmalloc(int len, t_trash **trash)
{
	char	*str;

	str = malloc(len);
	if (!str)
	{
		g_data.exit_status = 2;
		printf("malloc failed: try again !\n");
		return (NULL);
	}
	ft_bzero(str, len);
	add_to_trash(str, trash);
	return (str);
}
