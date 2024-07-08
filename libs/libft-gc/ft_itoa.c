/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jullopez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:21:18 by jullopez          #+#    #+#             */
/*   Updated: 2024/02/26 09:34:50 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft-gc.h"

static unsigned int	ft_absolute(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static int	ft_log(int n)
{
	int	l;

	l = 0;
	while (ft_absolute(n) >= 10 && ++l)
		n /= 10;
	return (l);
}

char	*ft_itoa(int n)
{
	int		size;
	int		sign;
	char	*ptr;

	sign = n < 0;
	size = ft_log(n) + 1 + sign;
	ptr = (char *) gc_calloc((size + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (size-- > sign)
	{
		ptr[size] = ft_absolute(n % 10) + 48;
		n /= 10;
	}
	if (sign)
		ptr[size] = '-';
	return (ptr);
}
/*
#include <stdio.h>

int	main(void)
{
	int	n = 0000;
	printf("%s\n", ft_itoa(n));
	printf("log = %d\n", ft_log(n));
	return (0);
}*/
