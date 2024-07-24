/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 22:13:35 by ohammou-          #+#    #+#             */
/*   Updated: 2023/11/24 15:12:22 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*b;

	i = 0;
	if (!s || !f)
		return (NULL);
	b = malloc(ft_strlen(s) + 1);
	if (!b || !s)
		return (NULL);
	while (s[i])
	{
		b[i] = f(i, s[i]);
		i++;
	}
	b[i] = '\0';
	return (b);
}
