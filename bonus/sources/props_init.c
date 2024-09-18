/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   props_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:55:57 by jullopez          #+#    #+#             */
/*   Updated: 2024/09/11 16:25:37 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minirt.h"

int	ambient_init(t_scene *scene, char **args)
{
	if (scene->ambient)
		return (ft_err("You cannot provide two ambient lightning", 0), -1);
	scene->ambient = gc_calloc(sizeof(struct s_ambient));
	if (!scene->ambient)
		return (-1);
	if (ft_strlen2(args) != 3)
		return (ft_err("Bad arguments number ambiant", 0), -1);
	if (set_ratio(args[1], &scene->ambient->light_ratio) == -1)
		return (ft_err("Bad ratio number ambiant", 0), -1);
	if (set_rgb(args[2], &scene->ambient->color) == -1)
		return (ft_err("Bad RGB arguments ambiant", 0), -1);
	return (0);
}

int	camera_init(t_scene *scene, char **args)
{
	if (scene->cam)
		return (ft_err("Scene can't have multiple cameras", 0), -1);
	scene->cam = gc_calloc(sizeof(struct s_cam));
	if (!scene->cam)
		return (-1);
	if (ft_strlen2(args) != 4)
		return (ft_err("Bad arguments number camera", 0), -1);
	if (set_vector3d(&scene->cam->pos, args[1]) == -1)
		return (ft_err("Bad coordinate for camera", 0), -1);
	if (set_normalized_vector3d(&scene->cam->dir, args[2]) == -1)
		return (ft_err("Bad arguments 3D vector camera", 0), -1);
	if (set_fov(args[3], &scene->cam->fov) == -1)
		return (ft_err("Bad fov for camera", 0), -1);
	return (0);
}

int	triangle_init(t_scene *scene, char **args)
{
	t_object	*triangle;

	triangle = gc_calloc(sizeof(t_object));
	if (!triangle)
		return (-1);
	if (ft_strlen2(args) != 5)
		return (ft_err("Bad arguments number triangle", 0), -1);
	if (set_vector3d(&triangle->v0, args[1]) == -1)
		return (ft_err("Bad coordinate v0 triangle", 0), -1);
	if (set_vector3d(&triangle->v1, args[2]) == -1)
		return (ft_err("Bad coordinate v1 triangle", 0), -1);
	if (set_vector3d(&triangle->v2, args[3]) == -1)
		return (ft_err("Bad coordinate v2 triangle", 0), -1);
	if (set_rgb(args[4], &triangle->color) == -1)
		return (ft_err("Bad rgb triangle", 0), -1);
	triangle->type = TRIANGLE;
	triangle->a = sub_vec3(triangle->v1, triangle->v0);
	triangle->b = sub_vec3(triangle->v2, triangle->v0);
	triangle->c = merge_vect(triangle->a, triangle->b);
	add_object(scene, triangle);
	return (0);
}
