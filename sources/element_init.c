/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:42:19 by akinzeli          #+#    #+#             */
/*   Updated: 2024/07/12 14:08:49 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

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

int	set_diameter(char *size, float *diameter)
{
	if (check_HD(size) == -1)
		return (-1);
	*diameter = (float)ft_atof(size);
	return (0);
}

int	set_height(char *size, float *height)
{
	if (check_HD(size) == -1)
		return (-1);
	*height = (float)ft_atof(size);
	return (0);
}

int	set_fov(char *fov, t_u8b *new_fov)
{
	int	i;
	int	num;

	i = 0;
	while (fov[i] != '\0')
	{
		if (!(fov[i] >= '0' && fov[i] <= '9'))
			return (-1);
		i++;
	}
	if (i > 3)
		return (-1);
	num = ft_atoi(fov);
	if (num < 0 || num > 180)
		return (-1);
	*new_fov = num;
	return (0);
}
