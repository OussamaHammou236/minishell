/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:17:09 by ohammou-          #+#    #+#             */
/*   Updated: 2023/11/24 15:10:10 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_hsb(char const *s, char c)
{
	int	hsb;

	hsb = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			hsb++;
			while (*s && *s != c)
				s++;
		}
	}
	return (hsb);
}

static char	**ft_free(char **b, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(b[i]);
		j++;
	}
	free(b);
	return (NULL);
}

static char	**ft_malloc(char const *s, char c, char **b)
{
	size_t	i;
	int		j;
	size_t	n;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		n = 0;
		while (s[i] != c && s[i])
		{
			i++;
			n++;
		}
		if (n > 0)
		{
			b[j] = ft_substr(&s[i - n], 0, n);
			if (!b[j])
				return (ft_free(b, j));
			j++;
		}
	}
	return (b);
}

char	**ft_split(char const *s, char c)
{
	char	**b;
	int		y;

	if (!s)
		return (malloc(0));
	y = ft_hsb(s, c);
	b = (char **)malloc((y + 1) * sizeof(char *));
	if (!b)
		return (NULL);
	b[y] = NULL;
	return (ft_malloc(s, c, b));
}
