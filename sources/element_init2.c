/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_init2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:08:28 by akinzeli          #+#    #+#             */
/*   Updated: 2024/07/12 14:08:51 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

int	set_vector3D(t_vec3 *vec, char *coordinate)
{
	char	**new;

	new = ft_split(coordinate, ",");
	if (ft_strlen2(new) != 3)
		return (-1);
	if (check_coordinate_value(new) == -1)
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