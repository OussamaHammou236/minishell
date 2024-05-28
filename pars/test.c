/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:25:11 by ohammou-          #+#    #+#             */
/*   Updated: 2024/05/28 13:44:27 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* ls > cd < dod $USER 
*/

void divide_cmd(char *str)
{
	t_data data;
	data.i = 0;
	data.len = ft_strlen(str) - 1;
	while (str[data.i] && str[data.i] != '>' && str[data.i] != '<')
		data.i++;
	while(str[data.len] && str[data.len] != '>' && str[data.len] != '<');
		data.len--;
	while(str[data.len] && str[data.len] == ' ')
		data.len++;
	while(str[data.len] && str[data.len] != ' ' )
		data.len++;
}
