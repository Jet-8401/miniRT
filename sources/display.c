/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jullopez <jullopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:11:30 by jullopez          #+#    #+#             */
/*   Updated: 2024/07/15 21:11:31 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

int	ft_init_display(t_scene *scene, int size_x, int size_y, char *title)
{
	scene->display.mlx_ptr = gc_track(mlx_init());
	if (!scene->display.mlx_ptr)
		return (ft_err(ERR_MLX_PTR, 0), -1);
	scene->display.height = size_y;
	scene->display.width = size_x;
	scene->display.aspect_ratio = (float) size_y / size_x;
	scene->display.scale = tan((float) scene->cam->fov / 2 * M_PI / 180);
	scene->display.window = mlx_new_window(scene->display.mlx_ptr, size_x, size_y, title);
	if (!scene->display.window)
		return (ft_err(ERR_MLX_WINDOW, 0), -1);
	scene->display.render_img = mlx_new_image(scene->display.mlx_ptr, size_x, size_y);
	if (!scene->display.render_img)
		return (ft_err(ERR_RENDER_IMG, 0), -1);
	scene->display.data = (uint32_t *) mlx_get_data_addr(scene->display.render_img,
		&scene->display.bpp, &scene->display.lsize, &scene->display.big_endian);
	scene->display.fps_counter = gc_calloc(sizeof(t_fpscounter));
	if (!scene->display.fps_counter)
		return (ft_err(ERR_COUNTER_INIT, 0), -1);
	fps_counter_init(scene->display.fps_counter, FPS_SNAPSHOT_SAMPLES);
	return (0);
}

void	ft_destroy_display(t_display *display)
{
	mlx_destroy_image(display->mlx_ptr, display->render_img);
	mlx_destroy_window(display->mlx_ptr, display->window);
	mlx_destroy_display(display->mlx_ptr);
	gc_free(display->mlx_ptr);
}
