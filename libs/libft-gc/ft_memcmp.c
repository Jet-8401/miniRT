/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Julien Lopez <marvin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:39:35 by Julien Lopez      #+#    #+#             */
/*   Updated: 2024/02/26 09:38:16 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft-gc.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (
		i < n - 1
		&&*((unsigned char *) s1 + i) == *((unsigned char *) s2 + i)
	)
		i++;
	return (*((unsigned char *) s1 + i) - *((unsigned char *) s2 + i));
}
