/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:31:08 by akinzeli          #+#    #+#             */
/*   Updated: 2024/09/01 23:35:43 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

int init_mlx_all(t_scene *scene)
{
    t_mlx *mlx;

    mlx = gc_calloc(sizeof(t_mlx));
    if (!mlx)
        return (-1);
    mlx->mlx = mlx_init();
    if (!mlx->mlx)
        return (ft_err("mlx_init failed", 0), -1);
    if (init_mlx_window(mlx) == -1)
        return (-1);
    mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
    if (!mlx->img.img)
        return (ft_err("mlx_new_image failed", 0), -1);
    mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bpp, &mlx->img.line_len, &mlx->img.endian);
    mlx->fps_counter = gc_calloc(sizeof(t_fpscounter));
    if (!mlx->fps_counter)
        return (ft_err("gc_calloc failed", 0), -1);
    fps_counter_init(mlx->fps_counter, FPS_SNAPSHOT_SAMPLES);
    scene->mlx = mlx;
    init_camera(scene);
    init_objects_all(scene);
    return (0);
}

void	ft_destroy_display(t_scene *display)
{
	mlx_destroy_image(display->mlx->mlx, display->mlx->img.img);
	mlx_destroy_window(display->mlx->mlx, display->mlx->win);
	mlx_destroy_display(display->mlx->mlx);
	gc_free(display->mlx->mlx);
}


int init_mlx_window(t_mlx *mlx)
{
    mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "miniRT");
    if (!mlx->win)
    {
        destroy_mlx(mlx);
        return (ft_err("mlx_new_window failed", 0), -1);
    }
    return (0);
}

void destroy_mlx(t_mlx *mlx)
{
    if (mlx->img.img)
        mlx_destroy_image(mlx->mlx, mlx->img.img);
    if (mlx->win)
        mlx_destroy_window(mlx->mlx, mlx->win);
    if (mlx->mlx)
        mlx_destroy_display(mlx->mlx);
    gc_free(mlx);
}

void new_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
    char *pixel;
    int i;

    i = mlx->img.bpp - 8;
    pixel = mlx->img.addr + (y * mlx->img.line_len + x * (mlx->img.bpp / 8));
    while (i >= 0)
    {
        if (mlx->img.endian != 0)
            *pixel++ = (color >> i) & 0xFF;
        else
            *pixel++ = (color >> (mlx->img.bpp - 8 - i)) & 0xFF;
        i -= 8;
    }
}

