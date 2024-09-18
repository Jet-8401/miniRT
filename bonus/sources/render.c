/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:45:59 by akinzeli          #+#    #+#             */
/*   Updated: 2024/09/11 16:24:56 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minirt.h"
#include <semaphore.h>
#include <strings.h>
#include <unistd.h>

void	init_camera(t_scene *scene)
{
	t_screen	*screen;

	screen = &scene->screen;
	screen->width = WIDTH;
	screen->height = HEIGHT;
	screen->scale = tan((float) scene->cam->fov / 2 * M_PI / 180);
	screen->aspect_ratio = screen->scale / ((float) WIDTH / HEIGHT);
	screen->right = normalize(merge_vect(scene->cam->dir,
				(t_vec3){0.0, 1.0, 0.0}));
	screen->up = normalize(merge_vect(scene->cam->dir, screen->right));
	screen->right = normalize(merge_vect(scene->cam->dir, screen->up));
}

// This is a proper way to create a pixel put function however very slow
void	new_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	uint8_t	*pixel;
	int		i;

	i = mlx->img.bpp - 8;
	pixel = mlx->img.addr + (y * mlx->img.line_len + x * (mlx->img.bpp / 8));
	while (i >= 0)
	{
		if (mlx->img.big_endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (mlx->img.bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	init_ray(t_scene *scene, t_ray_view *prime_ray, float x, float y)
{
	t_vec3	vertical;
	t_vec3	horizontal;
	t_vec3	res;

	prime_ray->origin = scene->cam->pos;
	prime_ray->direction.x = ((2.0f * x) / WIDTH) - 1;
	prime_ray->direction.y = ((2.0f * y) / HEIGHT) - 1;
	vertical = mult_vec3(scene->screen.up, prime_ray->direction.y
			* scene->screen.aspect_ratio);
	horizontal = mult_vec3(scene->screen.right, prime_ray->direction.x
			* scene->screen.scale);
	res = add_vec3(vertical, horizontal);
	res = add_vec3(res, scene->cam->dir);
	res = add_vec3(res, scene->cam->pos);
	prime_ray->direction = sub_vec3(res, prime_ray->origin);
	vec3_normalize(&prime_ray->direction);
}

int	render_scene(t_threads_container *threads)
{
	uint16_t	t;

	t = 0;
	while (t < threads->threads_number)
	{
		pthread_create(&threads->threads[t].thread_id, NULL, thread_routine,
			&threads->threads[t]);
		t++;
	}
	t = 0;
	while (t < threads->threads_number)
		pthread_join(threads->threads[t++].thread_id, NULL);
	mlx_put_image_to_window(threads->scene->mlx.mlx, threads->scene->mlx.win,
		threads->scene->mlx.img.img, 0, 0);
	fps_display(&threads->scene->mlx);
	threads_display(&threads->scene->mlx, threads);
	vec3_add(&threads->scene->cam->movements, &threads->scene->cam->pos,
		&threads->scene->cam->pos);
	return (0);
}
