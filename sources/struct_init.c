/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:40:03 by akinzeli          #+#    #+#             */
/*   Updated: 2024/07/11 17:19:42 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

int	add_camera_value(t_scene *scene, char **args)
{
	add_coordinate(args[1], &scene->cam.pos);
	if (add_3dvector(args[2], &scene->cam.dir) == -1)
		return (-1);
	if (add_fov(args[3], &scene->cam.fov) == -1)
		return (-1);
	return (0);
}

int	add_ambiant_value(t_scene *scene, char **args)
{
	if (add_ratio(args[1], &scene->ambient.light_ratio) == -1)
		return (-1);
	if (add_rgb(args[2], &scene->ambient.color) == -1)
		return (-1);
	return (0);
}

int	add_light_value(t_scene *scene, char **args)
{
	add_coordinate(args[1], &scene->light->pos);
	if (add_ratio(args[2], &scene->light->brightness) == -1)
		return (-1);
	return (0);
}

int	add_sphere_value(t_scene *scene, char **args)
{
	add_coordinate(args[1], &scene->sphere->pos);
	add_diameter(args[2], &scene->sphere->diameter);
	if (add_rgb(args[3], &scene->sphere->color) == -1)
		return (-1);
	return (0);
}

int	add_plane_value(t_scene *scene, char **args)
{
	add_coordinate(args[1], &scene->plane->pos);
	if (add_3dvector(args[2], &scene->plane->dir) == -1)
		return (-1);
	if (add_rgb(args[3], &scene->plane->color) == -1)
		return (-1);
	return (0);
}

