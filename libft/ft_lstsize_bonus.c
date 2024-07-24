/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 22:18:53 by ohammou-          #+#    #+#             */
/*   Updated: 2024/07/21 21:00:21 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_input *lst)
{
	int	i;

	i = 0;
	if (lst != NULL)
	{
		i = 1;
		while (lst->next != NULL)
		{
			i++;
			lst = lst->next;
		}
	}
	return (i);
}
