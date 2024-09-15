/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jullopez <jullopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:54:35 by jullopez          #+#    #+#             */
/*   Updated: 2024/09/13 18:54:35 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minirt.h"

static void	thread_render(t_render_thread *thread)
{
	uint64_t	x;
	uint64_t	y;

	x = thread->x_coords;
	y = thread->y_coords;
	while (y < thread->scene->screen.height)
	{
		while (x < thread->scene->screen.width)
		{
			init_ray(thread->scene, &thread->render.prime_ray, (float)x, (float)y);
			thread->render.color_ambiant = convert_rgb(&thread->scene->mlx,
					ambiant_color(&thread->render, thread->scene));
			new_mlx_pixel_put(&thread->scene->mlx, x, y, thread->render.color_ambiant);
			x++;
		}
		x = 0;
		y++;
	}
	sem_post(&thread->render_lock);
}

void	*thread_routine(void *arg)
{
	t_render_thread	*thread;

	thread = arg;
	while (1) // to change
	{
		thread_render(thread);
		//sem_wait(&thread->thread_lock);
	}
	exit(0);
	return (NULL);
}
