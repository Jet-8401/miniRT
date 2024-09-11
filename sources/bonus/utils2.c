/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:18:15 by akinzeli          #+#    #+#             */
/*   Updated: 2024/09/11 14:27:32 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/bonus_header/minirt.h"

t_u8b	check_data(int n, int min, int max)
{
	if (n > max)
		return (max);
	else if (n < min)
		return (min);
	return (n);
}

uint32_t	convert_rgb(t_mlx *mlx, t_rgb rgb)
{
	if (mlx->img.big_endian)
		return ((rgb.r << 24) | (rgb.g << 16) | (rgb.b << 8));
	else
		return ((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}
