/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 21:23:09 by ohammou-          #+#    #+#             */
/*   Updated: 2023/11/24 15:09:41 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int			i;
	long int	l;

	i = 0;
	l = n;
	if (fd < 0)
		return ;
	if (l < 0)
	{
		write(fd, "-", 1);
		l *= -1;
	}
	if (l >= 10)
	{
		ft_putnbr_fd(l / 10, fd);
		ft_putchar_fd(l % 10 + '0', fd);
	}
	if (l >= 0 && l < 10)
		ft_putchar_fd(l + '0', fd);
}
