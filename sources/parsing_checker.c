/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:36:17 by akinzeli          #+#    #+#             */
/*   Updated: 2024/07/11 11:37:35 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

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

int	check_3d_vector(char *vector)
{
	char	**new;

	new = ft_split(vector, ",");
	if (ft_strlen2(new) != 3)
		return (-1);
	if (check_3dvector_value(new) == -1)
		return (-1);
	return (0);
}

int	check_3dvector_value(char **vector)
{
	int	i;
	int	j;

	i = 0;
	while (vector[i] != NULL)
	{
		j = 0;
		if (vector[i][j] == '-')
			j++;
		else if (vector[i][j] == '.')
			return (-1);
		while (vector[i][j] != '\0')
		{
			if (vector[i][j] == '-')
				return (-1);
			else if (!(vector[i][j] >= '0' && vector[i][j] <= '9')
				|| vector[i][j] != '.')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_coordinate(char *coordinate)
{
	char	**new;

	new = ft_split(coordinate, ",");
	if (ft_strlen2(new) != 3)
		return (-1);
	if (check_coordinate_value(new) == -1)
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
			if ((coordinate[i][j] == '-'))
				return (-1);
			else if (!(coordinate[i][j] >= '0' && coordinate[i][j] <= '9')
				|| coordinate[i][j] != '.')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}
