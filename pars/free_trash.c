/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_trash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:56:12 by ohammou-          #+#    #+#             */
/*   Updated: 2024/07/04 18:00:33 by oumondad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_trash	*lstnew_of_trash(void *adr)
{
	t_trash	*node;

	node = malloc(sizeof(t_trash));
	if (!node)
		return (NULL);
	node->adr = adr;
	node->next = 0x0;
	return (node);
}

t_trash	*lstlast(t_trash *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	lstadd_back_to_trash(t_trash **lst, t_trash *new)
{
	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	lstlast(*lst)->next = new;
}

void	add_to_trash(void *adr, t_trash **lst)
{
	t_trash	*new_adr;

	new_adr = lstnew_of_trash(adr);
	lstadd_back_to_trash(lst, new_adr);
}

void	free_trash(t_trash **trash)
{
	void	*tmp;

	while (*trash)
	{
		tmp = *trash;
		free((*trash)->adr);
		*trash = (*trash)->next;
		free(tmp);
	}
}
