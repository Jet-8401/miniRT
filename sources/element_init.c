/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:42:19 by akinzeli          #+#    #+#             */
/*   Updated: 2024/07/12 13:11:34 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

int	add_fov(char *fov, t_u8b *new_fov)
{
	int	num;

	num = ft_atoi(fov);
	if (num < 0 || num > 180)
		return (-1);
	*new_fov = num;
	return (0);
}

int	add_3dvector(char *vector, t_vec3 *dir)
{
	char	**new;
	double	x;
	double	y;
	double	z;

	new = ft_split(vector, ",");
	x = ft_atof(new[0]);
	y = ft_atof(new[1]);
	z = ft_atof(new[2]);
	if ((x < -1.0 || x > 1.0) || (y < -1.0 || y > 1.0) || (z < -1.0 || z > 1.0))
		return (-1);
	(*dir).x = x;
	(*dir).y = y;
	(*dir).z = z;
	return (0);
}

int	add_coordinate(char *coor, t_vec3 *loc)
{
	char	**new;

	new = ft_split(coor, ",");
	(*loc).x = ft_atof(new[0]);
	(*loc).y = ft_atof(new[1]);
	(*loc).z = ft_atof(new[2]);
	return (0);
}

int	set_ratio(char *ratio, float *new_ratio)
{
	float	res;

	if (check_ratio(ratio) == -1)
		return (-1);
	res = (float)ft_atof(ratio);
	if (res < 0.0f || res > 1.0f)
		return (-1);
	*new_ratio = res;
	return (0);
}

int	set_rgb(char *rgb, t_rgb *color)
{
	char	**new;
	int		r;
	int		g;
	int		b;

	if (check_rgb(rgb) == -1)
		return (-1);
	new = ft_split(rgb, ",");
	r = ft_atoi(new[0]);
	g = ft_atoi(new[1]);
	b = ft_atoi(new[2]);
	if ((r < 0 || r > 255) && (g < 0 || g > 255) && (b < 0 || b > 255))
		return (-1);
	(*color).r = r;
	(*color).g = g;
	(*color).b = b;
	return (0);
}
