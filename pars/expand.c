/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:33:03 by ohammou-          #+#    #+#             */
/*   Updated: 2024/05/18 20:36:18 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
  
char *expande(char *str,int len)
{
	t_data data;
	data.i = 0;
	data.str = malloc(len + 1);

	while (str[data.i])
	{
		
	}
}