/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Julien Lopez <marvin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 02:04:49 by Julien Lopez      #+#    #+#             */
/*   Updated: 2024/02/26 09:38:09 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft-gc.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*((unsigned char *) s + i) == (unsigned char) c)
			return ((unsigned char *) s + i);
		i++;
	}
	return (NULL);
}
