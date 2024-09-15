/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jullopez <jullopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:54:36 by jullopez          #+#    #+#             */
/*   Updated: 2024/09/13 17:54:37 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minirt.h"
#include <pthread.h>
#include <stdbool.h>

static int init_threads_locks(t_render_thread *thread)
{
	if (sem_init(&thread->render_lock, 0, 0) == -1
		|| sem_init(&thread->thread_lock, 0, 1) == -1
	)
		return (ft_err(ERR_MUTEX_INIT, 1), -1);
	return (0);
}

int	threads_init(t_scene *scene, t_threads_container *container,
	uint16_t threads_number, uint64_t rendering_pixels)
{
	uint16_t		t;
	uint64_t		pixel_index;
	uint64_t		delta;
	t_render_thread	*th;

	t = 0;
	pixel_index = 0;
	delta = rendering_pixels / threads_number;
	container->threads_number = threads_number;
	container->threads = gc_calloc(sizeof(t_render_thread) * threads_number);
	if (!container->threads)
		return (ft_err(ERR_THREAD_INIT, 1), -1);
	while (t < threads_number)
	{
		th = &container->threads[t];
		if (init_threads_locks(th) == -1)
			return (ft_err(ERR_SEMAPHORE_INIT, 1), -1);
		th->container = container;
		th->x_coords = pixel_index / scene->screen.width;
		th->y_coords = pixel_index / scene->screen.height;
		th->pixel_length = delta;
		printf("thread #%d (x;y) (%ld;%ld)", t, th->x_coords, th->y_coords);
		printf(" (%ld ptp)\n", delta);
		th->scene = scene;
		pixel_index += delta;
		if (pthread_create(&th->thread_id, NULL, thread_routine, th) == -1)
			return (ft_err(ERR_THREAD_INIT, 1), -1);
		t++;
	}
	return (0);
}

void	wait_threads_routines(t_threads_container *container)
{
	uint16_t	routines_done;

	routines_done = 0;
	while (routines_done++ < container->threads_number)
	{
		printf("waiting routine of threads (%d/%d)\n", routines_done,
			container->threads_number);
	}
	printf("all threads routines have been done !\n");
	return ;
}

void	threads_display(t_mlx *mlx, t_threads_container *threads)
{
	static char	*threads_number;

	threads_number = ft_itoa(threads->threads_number);
	mlx_string_put(mlx->mlx, mlx->win, 0, 24, WHITE, "Threads: #");
	mlx_string_put(mlx->mlx, mlx->win, 60, 24, WHITE, threads_number);
	gc_free(threads_number);
	return ;
}
