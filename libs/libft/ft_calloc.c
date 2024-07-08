/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Julien Lopez <marvin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:11:07 by Julien Lopez      #+#    #+#             */
/*   Updated: 2024/02/28 08:54:01 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Note :
 * some report that the moulinette won't work if the inputs
 * can exceed the max int, maybe implement that later even tough
 * the code work like that
 */
void	*ft_calloc(size_t n, size_t size)
{
	void	*ptr;
	size_t	r;

	r = n * size;
	if (size && r / size != n)
		return (NULL);
	ptr = malloc(n * size);
	if (ptr)
		ft_bzero(ptr, n * size);
	return (ptr);
}
/*
int	main(void)
{
	int	*p = (int *) calloc(0x7FFFFFFF, sizeof(int));
	int	*d = (int *) ft_calloc(0x7FFFFFFF, sizeof(int));
	free(p);
	free(d);
	return (0);
}*/
