/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:17:09 by ohammou-          #+#    #+#             */
/*   Updated: 2024/07/01 10:32:44 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_input	*ft_lstnew()
{
	t_input	*node;

	node = malloc(sizeof(t_input));
	if (!node)
		return (NULL);
	node->next = 0x0;
	return (node);
}
