/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:36:17 by akinzeli          #+#    #+#             */
/*   Updated: 2024/07/12 14:08:10 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"
#include <math.h>

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

int	check_ratio(char *ratio)
{
	int	i;

	i = 0;
	while (ratio[i] != '\0')
	{
		if ((ratio[i] >= '0' && ratio[i] <= '1'))
			i++;
		if (ratio[i] == '.')
			i++;
		if (ratio[i] >= '0' && ratio[i] <= '9')
		{
			if (ratio[0] == 1 && ratio[i] != '0')
				return (-1);
			i++;
		}
		if (ratio[i] == '\0')
			return (1);
	}
	return (-1);
}

int	check_rgb(char *rgb)
{
	char	**color;

	color = ft_split(rgb, ",");
	if (ft_strlen2(color) != 3)
		return (-1);
	if (check_rgb_value(color) == -1)
		return (-1);
	return (0);
}

int	check_rgb_value(char **color)
{
	int	i;
	int	j;

	i = 0;
	while (color[i] != NULL)
	{
		j = 0;
		while (color[i][j] != '\0')
		{
			if (color[i][j] >= '0' && color[i][j] <= '9')
				j++;
			else
				return (-1);
		}
		i++;
	}
	return (0);
}

int	check_HD(char *hd)
{
	int	i;

	i = 0;
	printf("hd = %s.\n", hd);
	if (hd[i] == '.')
		return (-1);
	while (hd[i] != '\0')
	{
		if (!(hd[i] >= '0' && hd[i] <= '9') && hd[i] != '.')
			return (-1);
		i++;
	}
	return (0);
}
