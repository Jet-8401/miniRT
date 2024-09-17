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
#include <semaphore.h>

static int	locks_init(t_render_thread *th)
{
	if (sem_init(&th->render_lock, 0, 0) == -1
		|| sem_init(&th->thread_lock, 0, 1) == -1)
		return (-1);
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
	container->do_exit = 0;
	container->threads = gc_calloc(sizeof(t_render_thread) * threads_number);
	if (!container->threads)
		return (ft_err(ERR_THREAD_INIT, 1), -1);
	if (pthread_mutex_init(&container->data_lock, NULL) == -1)
		return (ft_err(ERR_MUTEX_INIT, 1), -1);
	printf("height=%ld * width=%ld = %ld pixels\n", scene->screen.height,
		scene->screen.width, rendering_pixels);
	printf("%ld / %d(threads) = %f\n", rendering_pixels, threads_number,
		(float) rendering_pixels / threads_number);
	while (t < threads_number)
	{
		th = &container->threads[t];
		if (locks_init(th) == -1)
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

void	threads_display(t_mlx *mlx, t_threads_container *threads)
{
	static char	*threads_number;

	threads_number = ft_itoa(threads->threads_number);
	mlx_string_put(mlx->mlx, mlx->win, 0, 24, WHITE, "Threads: #");
	mlx_string_put(mlx->mlx, mlx->win, 60, 24, WHITE, threads_number);
	gc_free(threads_number);
	return ;
}
