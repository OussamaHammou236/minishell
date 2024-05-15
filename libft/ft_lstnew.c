/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:17:09 by ohammou-          #+#    #+#             */
/*   Updated: 2024/04/25 16:35:51 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_input	*ft_lstnew(char **content)
{
	t_input	*node;

	node = malloc(sizeof(t_input));
	if (!node)
		return (NULL);
	node->cmd = content;
	node->type = 0;
	node->next = 0x0;
	return (node);
}
