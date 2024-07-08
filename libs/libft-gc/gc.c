/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jullopez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 09:26:22 by jullopez          #+#    #+#             */
/*   Updated: 2024/06/13 21:29:11 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

t_gc	**gc_interface(void *hook)
{
	static t_gc	*g_gc = NULL;

	if (hook)
		g_gc = hook;
	return (&g_gc);
}

/* Add an address at the top of the stack of the garbage collector.
 */
void	*gc_track(void *address)
{
	t_gc	**g_gc;
	t_gc	*node;

	node = (t_gc *) malloc(sizeof(t_gc));
	if (!node)
		return (gc_error(GC_ALLOC_ERR), gc_error(GC_TRACK_ERR), address);
	node->prev = NULL;
	node->address = address;
	g_gc = gc_interface(NULL);
	if (*g_gc)
		node->prev = *g_gc;
	*g_gc = node;
	return (address);
}
