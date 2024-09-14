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

static int init_threads_locks(t_threads_container *container)
{
	if (sem_init(&container->image_rendering, 0, container->threads_number)
		== -1 || sem_init(&container->threads_routines, 0, 0) == -1
	)
		return (ft_err(ERR_MUTEX_INIT, 1), -1);
	return (0);
}

int	threads_init(t_scene *scene, t_threads_container *container,
	uint16_t threads_number, uint64_t rendering_pixels)
{
	uint16_t		t;
	uint64_t		pixel_index;
	int				delta;
	t_render_thread	*th;

	t = 0;
	pixel_index = 0;
	delta = rendering_pixels / threads_number;
	container->threads_number = threads_number;
	container->threads = gc_calloc(sizeof(t_render_thread) * threads_number);
	if (!container->threads || init_threads_locks(container) == -1)
		return (ft_err(ERR_THREAD_INIT, 1), -1);
	while (t < threads_number)
	{
		th = &container->threads[t];
		if (pthread_mutex_init(&th->render_lock, NULL) == -1)
			return (ft_err(ERR_MUTEX_INIT, 1), -1);
		th->container = container;
		th->pixel_offset = pixel_index;
		th->pixel_length = delta;
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
		sem_wait(&container->threads_routines);
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
