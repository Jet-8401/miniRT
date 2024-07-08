/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Julien Lopez <marvin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 01:45:27 by Julien Lopez      #+#    #+#             */
/*   Updated: 2024/02/26 09:38:24 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft-gc.h"

/* Description
 * The memcpy() function copies n bytes from memory area src to memory
 * area dest. The memory areas must not overlap. Use memmove(3) if the
 * memory areas do overlap.
 * 
 * Return Value
 * The memcpy() function returns a pointer to dest.
 * void *ft_memcpy(void *dest, const void *src, size_t n)
 */
/*
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d_copy;
	unsigned char	*s_copy;

	i = 0;
	d_copy = (unsigned char *) dest;
	s_copy = (unsigned char *) src;
	while (i < n)
	{
		*(d_copy + i) = *(s_copy + i);
		i++;
	}
	return (dest);
}
*/

// There is an other way of doing so by dereferencing the void pointer
// directly into the while loop, but have to check if the processing
// time increase by doing so...
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!n || dest == src)
		return (dest);
	i = 0;
	while (i < n)
	{
		*((unsigned char *) dest + i) = *((unsigned char *) src + i);
		i++;
	}
	return (dest);
}
// More efficient way to do it...
// Just have to test it
/*void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	while (n-- != 0)
		*((unsigned char *) dest + n) = *((unsigned char *) src + n);
	return (dest);
}*/
