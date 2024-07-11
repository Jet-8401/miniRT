/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checker2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:38:11 by akinzeli          #+#    #+#             */
/*   Updated: 2024/07/11 12:24:24 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

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
	if (hd[i] == '.')
		return (-1);
	while (hd[i] != '\0')
	{
		if (!(hd[i] >= '0' && hd[i] <= '9') || hd[i] != '.')
			return (-1);
		i++;
	}
	return (0);
}
