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

static bool	set_thread(t_threads_container *container, t_scene *scene,
	uint8_t t, double delta)
{
	static uint64_t		pixel_index = 0;
	t_render_thread		*th;

	th = &container->threads[t];
	th->id = t;
	th->container = container;
	th->y_coords = pixel_index / scene->screen.width;
	th->x_coords = pixel_index - (th->y_coords * scene->screen.width);
	th->pixel_length = delta;
	th->scene = scene;
	pixel_index += delta;
	t++;
	return (1);
}

int	threads_init(t_scene *scene, t_threads_container *container,
	uint8_t threads_number)
{
	uint8_t			t;
	double_t		delta;
	uint64_t		rendering_pixels;

	rendering_pixels = scene->screen.height * scene->screen.width;
	if (threads_number == 0)
		return (ft_err(ERR_THREAD_NUMBER_ZERO, 0), -1);
	t = 0;
	delta = round((double) rendering_pixels / threads_number);
	container->threads_number = threads_number;
	container->do_exit = 0;
	container->threads = gc_calloc(sizeof(t_render_thread) * threads_number);
	if (!container->threads)
		return (ft_err(ERR_THREAD_INIT, 1), -1);
	if (pthread_mutex_init(&container->data_lock, NULL) == -1)
		return (ft_err(ERR_MUTEX_INIT, 1), -1);
	while (t < threads_number)
		if (!set_thread(container, scene, t++, delta))
			return (-1);
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
