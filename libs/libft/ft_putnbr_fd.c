/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jullopez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:41:12 by jullopez          #+#    #+#             */
/*   Updated: 2024/02/26 09:39:48 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_absolute(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n < 0)
		write(fd, "-", 1);
	if (n >= 10 || n <= -10)
		ft_putnbr_fd(ft_absolute(n / 10), fd);
	c = ft_absolute(n % 10) + 48;
	write(fd, &c, 1);
}
