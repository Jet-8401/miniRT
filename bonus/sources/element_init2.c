/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_init2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:08:28 by akinzeli          #+#    #+#             */
/*   Updated: 2024/09/11 16:24:56 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minirt.h"

int	set_vector3d(t_vec3 *vec, char *coordinate)
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

int	set_normalized_vector3d(t_vec3 *vec, char *coordinate)
{
	if (set_vector3d(vec, coordinate) == -1)
		return (-1);
	if ((vec->x < -1.0 || vec->x > 1.0) || (vec->y < -1.0 || vec->y > 1.0)
		|| (vec->z < -1.0 || vec->z > 1.0))
		return (-1);
	return (0);
}
