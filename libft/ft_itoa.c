/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:28:59 by ohammou-          #+#    #+#             */
/*   Updated: 2023/11/24 15:03:27 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_digitlen(int n)
{
	int	j;

	j = 0;
	if (n == 0)
		j++;
	while (n != 0)
	{
		n /= 10;
		j++;
	}
	return (j);
}

char	*ft_itoa(int n)
{
	int		c;
	int		j;
	char	*l;
	long	g;

	g = n;
	j = ft_digitlen(g);
	c = 0;
	if (g < 0)
	{
		g *= -1;
		c = 1;
	}
	l = malloc((c + j + 1) * sizeof(char));
	if (!l)
		return (NULL);
	if (c)
		l[0] = '-';
	l[j + c] = '\0';
	while (j-- > 0)
	{
		l[j + c] = (g % 10) + '0';
		g /= 10;
	}
	return (l);
}
