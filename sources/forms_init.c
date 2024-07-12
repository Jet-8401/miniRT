/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forms_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:52:05 by jullopez          #+#    #+#             */
/*   Updated: 2024/07/12 13:42:44 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

int	light_init(t_scene *scene, char **args)
{
	t_light	*light;

	light = gc_calloc(sizeof(t_light));
	if (!light)
		return (-1);
	if (ft_strlen2(args) != 4)
		return (ft_err("Bad arguments number light", 0), -1);
	if (set_vector3D(&light->pos, args[1]) == -1)
		return (ft_err("Bad coordinate light", 0), -1);
	if (set_ratio(args[2], &light->brightness) == -1)
		return (ft_err("Bad light ratio", 0), -1);
	scene->light = light;
	// if (add_light_value(scene, args) == -1)
	// return (ft_err("Wrong light values", 0), -1);
	return (0);
}

int	sphere_init(t_scene *scene, char **args)
{
	t_sphere	*sphere;

	sphere = gc_calloc(sizeof(t_sphere));
	if (!sphere)
		return (-1);
	if (ft_strlen2(args) != 4)
		return (ft_err("Bad arguments number sphere", 0), -1);
	if (set_vector3D(&sphere->pos, args[1]) == -1)
		return (ft_err("Bad argument coordinate sphere", 0), -1);
	if (set_diameter(args[2], &sphere->diameter) == -1)
		return (ft_err("Bad height sphere", 0), -1);
	if (set_rgb(args[3], &sphere->color) == -1)
		return (ft_err("Bad rgb arguments sphere", 0), -1);
	add_sphere(scene, sphere);
	// if (add_sphere_value(scene, args) == -1)
	// return (ft_err("Wrong sphere values", 0), -1);
	// add_object(&scene->sphere->next, sphere);
	return (0);
}

int	plane_init(t_scene *scene, char **args)
{
	t_plane	*plane;

	plane = gc_calloc(sizeof(t_plane));
	if (!plane)
		return (-1);
	if (ft_strlen2(args) != 4)
		return (ft_err("Bad arguments number plane", 0), -1);
	if (set_vector3D(&plane->pos, args[1]) == -1)
		return (ft_err("Bad argument coordinate sphere", 0), -1);
	if (set_normalized_vector3D(&plane->dir, args[2]) == -1)
		return (ft_err("Bad 3d vector plane", 0), -1);
	if (set_rgb(args[3], &plane->color) == -1)
		return (ft_err("Bad rgb plane", 0), -1);
	add_plane(scene, plane);
	// if (add_plane_value(scene, args) == -1)
	// return (ft_err("wrong plane values", 0), -1);
	return (0);
}

int	cylinder_init(t_scene *scene, char **args)
{
	t_cylinder	*cylinder;

	cylinder = gc_calloc(sizeof(t_cylinder));
	if (!cylinder)
		return (-1);
	if (ft_strlen2(args) != 6)
		return (ft_err("Bad arguments number cylinder", 0), -1);
	if (set_vector3D(&cylinder->pos, args[1]) == -1)
		return (ft_err("Bad coordinate cylinder", 0), -1);
	if (set_normalized_vector3D(&cylinder->dir, args[2]) == -1)
		return (ft_err("Bad 3d vector cylinder", 0), -1);
	if (set_diameter(args[3], &cylinder->diameter) == -1)
		return (ft_err("Bad diameter", 0), -1);
	if (set_height(args[4], &cylinder->height) == -1)
		return (ft_err("Bad height cylinder", 0), -1);
	if (set_rgb(args[5], &cylinder->color) == -1)
		return (ft_err("Bad rgb cylinder", 0), -1);
	add_cylinder(scene, cylinder);
	// if (add_cylinder_value(scene, args) == -1)
	// return (ft_err("wrong cylinder values", 0), -1);
	return (0);
}
