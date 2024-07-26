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
}

double	vec3D_dot(t_vec3 *a, t_vec3 *b)
{
	return ((a->x * b->x) + (a->y * b->y) + (a->z * b->z));
}
