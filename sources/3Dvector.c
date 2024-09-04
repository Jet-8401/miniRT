/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3Dvector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:08:28 by akinzeli          #+#    #+#             */
/*   Updated: 2024/07/15 23:27:25 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

int	set_vector3D(t_vec3 *vec, char *coordinate)
{
	char	**new;

	new = ft_split(coordinate, ",");
	if (ft_strlen2(new) != 3 || check_numbers_value(new, true) == -1)
		return (-1);
	vec->x = ft_atof(new[0]);
	vec->y = ft_atof(new[1]);
	vec->z = ft_atof(new[2]);
	return (0);
}

int	set_normalized_vector3D(t_vec3 *vec, char *coordinate)
{
	if (set_vector3D(vec, coordinate) == -1)
		return (-1);
	if ((vec->x < -1.0 || vec->x > 1.0) || (vec->y < -1.0 || vec->y > 1.0)
		|| (vec->z < -1.0 || vec->z > 1.0))
		return (-1);
	return (0);
}

void	vec3D_normalize(t_vec3 *vec)
{
	double	magnitude;

	magnitude = sqrt(((vec->x * vec->x) + (vec->y * vec->y) +
		(vec->z * vec->z)));
	vec->x /= magnitude;
	vec->y /= magnitude;
	vec->z /= magnitude;
	return ;
}

double	vec3D_dot(t_vec3 *a, t_vec3 *b)
{
	return ((a->x * b->x) + (a->y * b->y) + (a->z * b->z));
}

void	vec3D_cross(t_vec3 *a, t_vec3 *b, t_vec3 *c)
{
	c->x = a->x * b->z - a->z * b->y;
	c->y = a->z * b->x - a->x * b->z;
	c->z = a->x * b->y - a->y * b->x;
	return ;
}

void	vec3D_subtract(t_vec3 *a, t_vec3 *b, t_vec3 *c)
{
	c->x = a->x - b->x;
	c->y = a->y - b->y;
	c->z = a->z - b->z;
}

void	vec3D_add(t_vec3 *a, t_vec3 *b, t_vec3 *c)
{
	c->x = a->x + b->x;
	c->y = a->y + b->y;
	c->z = a->z + b->z;
}

void	vec3D_mult(t_vec3 *a, t_vec3 *b, t_vec3 *c)
{
	c->x = a->x * b->x;
	c->y = a->y * b->y;
	c->z = a->z * b->z;
}

void	vec3D_scale(t_vec3 *a, float scale, t_vec3 *b)
{
	b->x = a->x * scale;
	b->y = a->y * scale;
	b->z = a->z * scale;
}
