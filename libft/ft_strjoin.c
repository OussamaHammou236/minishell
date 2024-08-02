/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:52:27 by ohammou-          #+#    #+#             */
/*   Updated: 2024/08/01 15:42:26 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*b;

	if (!s1 || !s2)
		return (NULL);
	b = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!b)
		exit (1);
	ft_strlcpy(b, s1, ft_strlen(s1) + 1);
	ft_strlcat(b, s2, ft_strlen(s2) + ft_strlen(s1) + 1);
	return (b);
}
