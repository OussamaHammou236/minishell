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
  
char *expande(char *str,t_data *info)
{
	int i;
	char *s;

	i = 0;
	while(str[info->i + i] != ' ' && str[info->i + i] != '"' && str[info->i + i] != '\'' && str[info->i + i] != '\0')
		i++;
	s = ft_substr(str,info->i,i);
	printf("%s\n",s);
}