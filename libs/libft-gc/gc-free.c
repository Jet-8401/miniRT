/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc-free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:55:54 by jullopez          #+#    #+#             */
/*   Updated: 2024/06/20 20:25:15 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

void	gc_free(void *address)
{
	t_gc	*gc;
	t_gc	*after;
	t_gc	*copy;

	gc = *gc_interface(NULL);
	after = NULL;
	while (gc && gc->address != address)
	{
		after = gc;
		gc = gc->prev;
	}
	if (!gc)
		return ;
	copy = gc->prev;
	free(gc->address);
	free(gc);
	if (!after)
		gc_interface(copy);
	else
		after->prev = copy;
}

/* Dump all variables until address is encountered.
 * Note: address it dumped too.
 */
void	gc_dump(void *address)
{
	char	stop;
	t_gc	**g_gc;
	t_gc	*copy;

	stop = 0;
	g_gc = gc_interface(NULL);
	while (*g_gc && !stop)
	{
		if (address && (*g_gc)->address == address)
			stop = 1;
		copy = (*g_gc)->prev;
		free((*g_gc)->address);
		free(*g_gc);
		(*g_gc) = copy;
	}
}
