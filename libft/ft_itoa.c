/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iahamdan <iahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:54:46 by iahamdan          #+#    #+#             */
/*   Updated: 2024/06/27 16:02:29 by iahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*zero_error(void)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = 48;
	str[1] = '\0';
	return (str);
}

static int	calcule_len(long n)
{
	long	div;
	int		len;

	div = n;
	len = 0;
	while (div > 0)
	{
		len++;
		div = div / 10;
	}
	return (len);
}

static void	my_loop(long div, int len, char *str, int x)
{
	long	mod;

	while (len - 1 >= x)
	{
		mod = div % 10;
		div = div / 10;
		str[len - 1] = mod + 48;
		len--;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	div;
	int		x;

	x = 0;
	div = n;
	if (div == 0)
		return (zero_error());
	if (div < 0)
	{
		div *= -1;
		x++;
	}
	len = calcule_len(div) + x;
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	if (x == 1)
		str[0] = '-';
	my_loop(div, len, str, x);
	str[calcule_len(div) + x] = '\0';
	return (str);
}
