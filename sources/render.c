/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:45:59 by akinzeli          #+#    #+#             */
/*   Updated: 2024/09/11 11:23:36 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

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

void	pixel_draw(t_scene *scene, t_render *render)
{
	uint64_t	x;
	uint64_t	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			init_ray(scene, &render->prime_ray, (float)x, (float)y);
			render->color_ambiant = convert_rgb(&scene->mlx,
					ambiant_color(render, scene));
			new_mlx_pixel_put(&scene->mlx, x, y, render->color_ambiant);
			x++;
		}
		y++;
	}
}

int	render_scene(t_scene *scene)
{
	pixel_draw(scene, &scene->render);
	mlx_put_image_to_window(scene->mlx.mlx, scene->mlx.win,
		scene->mlx.img.img, 0, 0);
	fps_display(&scene->mlx);
	render_time_display(&scene->mlx);
	return (0);
}
