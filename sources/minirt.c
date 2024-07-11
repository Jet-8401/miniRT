/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:16:38 by jullopez          #+#    #+#             */
/*   Updated: 2024/07/11 17:19:49 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

int	main(int argc, char *argv[])
{
	t_scene	scene;

	(void)argc; // to remove
	if (ft_parsing(&scene, argv[1]) == -1)
		return (gc_dump(NULL), 0);
	print_all(&scene);
	gc_dump(NULL);
	return (0);
}

void	print_all(t_scene *scene)
{
	printf("Ambient light: %f\n", scene->ambient.light_ratio);
	printf("Ambient color: %d %d %d\n", scene->ambient.color.r, scene->ambient.color.g, scene->ambient.color.b);
	printf("Camera position: %f %f %f\n", scene->cam.pos.x, scene->cam.pos.y, scene->cam.pos.z);
	printf("Camera direction: %f %f %f\n", scene->cam.dir.x, scene->cam.dir.y, scene->cam.dir.z);
	printf("Camera fov: %d\n", scene->cam.fov);
	printf("Sphere position: %f %f %f\n", scene->sphere->pos.x, scene->sphere->pos.y, scene->sphere->pos.z);
	printf("Sphere diameter: %f\n", scene->sphere->diameter);
	printf("Sphere color: %d %d %d\n", scene->sphere->color.r, scene->sphere->color.g, scene->sphere->color.b);
	printf("Plane position: %f %f %f\n", scene->plane->pos.x, scene->plane->pos.y, scene->plane->pos.z);
	printf("Plane direction: %f %f %f\n", scene->plane->dir.x, scene->plane->dir.y, scene->plane->dir.z);
	printf("Plane diameter: %f\n", scene->plane->diameter);
	printf("Plane height: %f\n", scene->plane->height);
	printf("Plane color: %d %d %d\n", scene->plane->color.r, scene->plane->color.g, scene->plane->color.b);
	printf("Cylinder position: %f %f %f\n", scene->cylinder->pos.x, scene->cylinder->pos.y, scene->cylinder->pos.z);
	printf("Cylinder direction: %f %f %f\n", scene->cylinder->dir.x, scene->cylinder->dir.y, scene->cylinder->dir.z);
	printf("Cylinder diameter: %f\n", scene->cylinder->diameter);
	printf("Cylinder height: %f\n", scene->cylinder->height);
	printf("Cylinder color: %d %d %d\n", scene->cylinder->color.r, scene->cylinder->color.g, scene->cylinder->color.b);
	printf("Light position: %f %f %f\n", scene->light->pos.x, scene->light->pos.y, scene->light->pos.z);
	printf("Light brightness: %f\n", scene->light->brightness);
}
