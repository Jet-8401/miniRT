/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:36:17 by akinzeli          #+#    #+#             */
/*   Updated: 2024/07/11 16:51:00 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"
#include <math.h>

int	check_fov(char *fov)
{
	int	i;

	i = 0;
	while (fov[i] != '\0')
	{
		if (!(fov[i] >= '0' && fov[i] <= '9'))
			return (-1);
		i++;
	}
	if (i > 3)
		return (-1);
	return (0);
}

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
	if (set_vector3D(vec) == -1)
		return (-1);
	if ((vec->x < -1.0 || vec->x > 1.0) || (vec->y < -1.0 || vec->y > 1.0)
			|| (vec->z < -1.0 || vec->z > 1.0))
		return (-1);
	return (0);
}

int	check_coordinate_value(char **coordinate)
{
	int	i;
	int	j;

	i = 0;
	while (coordinate[i] != NULL)
	{
		j = 0;
		if (coordinate[i][j] == '-')
			j++;
		else if (coordinate[i][j] == '.')
			return (-1);
		while (coordinate[i][j] != '\0')
		{
			if (!(coordinate[i][j] >= '0' && coordinate[i][j] <= '9')
				&& coordinate[i][j] != '.')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}
