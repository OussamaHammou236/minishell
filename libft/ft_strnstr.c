/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 20:54:22 by ohammou-          #+#    #+#             */
/*   Updated: 2023/11/24 18:10:04 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *h, const char *n, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	b;

	j = 0;
	i = 0;
	if (!h && !len)
		return (NULL);
	if (n[0] == '\0')
		return ((char *)h);
	while (h[i])
	{
		j = 0;
		b = i;
		while (h[i] == n[j] && i < len)
		{
			if (n[j + 1] == '\0')
				return (&((char *)h)[b]);
			j++;
			i++;
		}
		i -= j;
		i++;
	}
	return (NULL);
}
