/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   props_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:55:57 by jullopez          #+#    #+#             */
/*   Updated: 2024/07/10 18:18:16 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

int	ambient_init(t_scene *scene, char **args)
{
	if (ft_strlen2(args) != 3)
		return (ft_err("Bad arguments number", 0), -1);
	if (check_ratio(args[1]) == -1)
		return (ft_err("Bad ratio number", 0), -1);
	if (check_rgb(args[2]) == -1)
		return (ft_err("Bad RGB arguments", 0), -1);
	if (add_ambiant_value(scene, args) == -1)
		return (ft_err("Wrong ambiant values", 0), -1);
	return (0);
}

int	camera_init(t_scene *scene, char **args)
{
	(void)scene;
	(void)args;
	return (0);
}

int	light_init(t_scene *scene, char **args)
{
	(void)scene;
	(void)args;
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

int	add_ambiant_value(t_scene *scene, char **args)
{
	if (add_ratio(args[1], &scene->ambient->light_ratio) == -1)
		return (-1);
	if (add_rgb(args[2], &scene->ambient->color) == -1)
		return (-1);
	return (0);
}

int	add_ratio(char *ratio, float *new_ratio)
{
	float	res;

	res = (float)ft_atof(ratio);
	if (res < 0.0f || res > 1.0f)
		return (-1);
	*new_ratio = res;
	return (0);
}

int	add_rgb(char *rgb, t_rgb *color)
{
	char **new;
	int r;
	int g;
	int b;

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