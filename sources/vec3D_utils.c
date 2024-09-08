/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3D_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jullopez <jullopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 01:50:04 by jullopez          #+#    #+#             */
/*   Updated: 2024/09/08 01:50:06 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

void	vec3_subtract(t_vec3 *a, t_vec3 *b, t_vec3 *result)
{
	result->x = a->x - b->x;
	result->y = a->y - b->y;
	result->z = a->z - b->z;
	return ;
}

void	vec3_add(t_vec3 *a, t_vec3 *b, t_vec3 *result)
{
	result->x = a->x + b->x;
	result->y = a->y + b->y;
	result->z = a->z + b->z;
	return ;
}

void	vec3_scale(t_vec3 *a, double scalar)
{
	a->x *= scalar;
	a->y *= scalar;
	a->z *= scalar;
	return ;
}

void	vec3_cross(t_vec3 *a, t_vec3 *b, t_vec3 *result)
{
	result->x = a->x * b->z - a->z * b->y;
	result->y = a->z * b->x - a->x * b->z;
	result->z = a->x * b->y - a->y * b->x;
	return ;
}

void	vec3_normalize(t_vec3 *vec)
{
	double	magnitude;

	magnitude = sqrt(((vec->x * vec->x) + (vec->y * vec->y) +
		(vec->z * vec->z)));
	vec->x /= magnitude;
	vec->y /= magnitude;
	vec->z /= magnitude;
	return ;
}

double	vec3_dot(t_vec3 *a, t_vec3 *b)
{
	return ((a->x * b->x) + (a->y * b->y) + (a->z * b->z));
}
