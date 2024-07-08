/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Julien Lopez <marvin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 01:45:27 by Julien Lopez      #+#    #+#             */
/*   Updated: 2024/02/26 09:38:55 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Description
 * The memset() function fills the first n bytes of the memory area
 * pointed to by s with the constant byte c.
 * 
 * Return Value
 * The memset() function returns a pointer to the memory area s.
 */
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s_copy;

	s_copy = (unsigned char *) s;
	while (n > 0)
		*(s_copy + (--n)) = c;
	return (s);
}
