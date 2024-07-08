/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jullopez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 09:21:56 by jullopez          #+#    #+#             */
/*   Updated: 2024/06/13 23:16:15 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include <stdlib.h>
# include <unistd.h>

# define GC_ERR "\x1b[1;32mgarbage-collector error: \n\x1b[0m"
# define GC_ALLOC_ERR "Impossible to alloc memory !\n"
# define GC_TRACK_ERR "An error occured while tracking an address !\n"

/*
 * For performance reasons the garbage collector
 * should be implemented as a binary tree (see later)
 */
typedef struct s_gc
{
	void		*address;
	struct s_gc	*prev;
}	t_gc;

/* utils.c */
void	gc_error(const char *msg);

/* gc.c */
t_gc	**gc_interface(void *hook);
void	*gc_track(void *address);

/* gc-alloc.c */
void	*gc_malloc(size_t size);
void	*gc_calloc(size_t size);

/* gc-free.c */
void	gc_dump(void *address);
void	gc_free(void *address);

#endif
