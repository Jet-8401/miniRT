/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc-alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jullopez <jullopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:54:34 by jullopez          #+#    #+#             */
/*   Updated: 2024/06/13 23:15:38 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

void	*gc_malloc(size_t size)
{
	void	*addr;

	addr = malloc(size);
	if (!addr)
		return (gc_error(GC_ALLOC_ERR), addr);
	return (gc_track(addr));
}

void	*gc_calloc(size_t size)
{
	size_t	i;
	void	*addr;

	i = 0;
	addr = gc_malloc(size);
	if (!addr)
		return (addr);
	while (i < size)
		*((unsigned char *) addr + i++) = 0;
	return (addr);
}
