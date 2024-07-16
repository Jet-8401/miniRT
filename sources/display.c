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

int	ft_init_display(t_display *display, int size_x, int size_y, char *title)
{
	display->mlx_ptr = gc_track(mlx_init());
	if (!display->mlx_ptr)
		return (ft_err(ERR_MLX_PTR, 0), -1);
	display->height = size_y;
	display->widht = size_x;
	display->window = mlx_new_window(display->mlx_ptr, size_x, size_y, title);
	if (!display->window)
		return (ft_err(ERR_MLX_WINDOW, 0), -1);
	display->render_img = mlx_new_image(display->mlx_ptr, size_x, size_y);
	if (!display->render_img)
		return (ft_err(ERR_RENDER_IMG, 0), -1);
	display->stream = (unsigned char *) mlx_get_data_addr(display->render_img,
		&display->bpp, &display->lsize, &display->big_endian);
	return (0);
}

void	ft_destroy_display(t_display *display)
{
	mlx_destroy_image(display->mlx_ptr, display->render_img);
	mlx_destroy_window(display->mlx_ptr, display->window);
	mlx_destroy_display(display->mlx_ptr);
	gc_free(display->mlx_ptr);
}
