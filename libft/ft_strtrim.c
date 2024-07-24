/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:30:29 by ohammou-          #+#    #+#             */
/*   Updated: 2023/11/25 09:29:24 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	i;
	size_t	j;
	char	*d;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	j = ft_strlen(s1) - 1;
	if (s1[i] == '\0')
		return (ft_strdup(""));
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (j > i && ft_strchr(set, s1[j]))
		j--;
	d = (char *)malloc(j - i + 2);
	if (!d)
		return (NULL);
	ft_strlcpy(d, &s1[i], j - i + 2);
	return (d);
}
