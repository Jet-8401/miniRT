/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:31:08 by akinzeli          #+#    #+#             */
/*   Updated: 2024/09/11 13:08:54 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

int	init_mlx_all(t_scene *scene)
{
	t_mlx	*mlx;

	mlx = &scene->mlx;
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (ft_err(ERR_MLX_PTR, 0), -1);
	if (init_mlx_window(mlx) == -1)
		return (-1);
	mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img.img)
		return (ft_err(ERR_RENDER_IMG, 0), -1);
	mlx->img.addr = (uint8_t *) mlx_get_data_addr(mlx->img.img, &mlx->img.bpp,
			&mlx->img.line_len, &mlx->img.big_endian);
	mlx->fps_counter = gc_calloc(sizeof(t_fpscounter));
	if (!mlx->fps_counter)
		return (ft_err(ERR_COUNTER_INIT, 0), -1);
	fps_counter_init(mlx->fps_counter, FPS_SNAPSHOT_SAMPLES);
	init_camera(scene);
	return (0);
}

void	ft_destroy_display(t_scene *display)
{
	mlx_destroy_image(display->mlx.mlx, display->mlx.img.img);
	mlx_destroy_window(display->mlx.mlx, display->mlx.win);
	mlx_destroy_display(display->mlx.mlx);
	free(display->mlx.mlx);
}

int	init_mlx_window(t_mlx *mlx)
{
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "miniRT");
	if (!mlx->win)
	{
		destroy_mlx(mlx);
		return (ft_err(ERR_MLX_WINDOW, 0), -1);
	}
	return (0);
}

void	destroy_mlx(t_mlx *mlx)
{
	if (mlx->img.img)
		mlx_destroy_image(mlx->mlx, mlx->img.img);
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->mlx)
		mlx_destroy_display(mlx->mlx);
	gc_free(mlx);
}
