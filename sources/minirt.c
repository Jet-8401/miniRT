/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:16:38 by jullopez          #+#    #+#             */
/*   Updated: 2024/07/15 23:26:50 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"
#include <X11/X.h>
#include <unistd.h>

void print_sphere_list(t_scene *scene)
{
	t_object *object;

	object = scene->objects;
	while (object)
	{
		if (object->type != SPEHRE)
		{
			object = object->next;
			continue ;
		}
		printf("Sphere position: %f %f %f\n", object->pos.x, object->pos.y, object->pos.z);
		printf("Sphere diameter: %f\n", object->radius);
		printf("Sphere color: %d %d %d\n", object->color.r, object->color.g, object->color.b);
		object = object->next;
	}
}

void print_plane_list(t_scene *scene)
{
	t_object *object;

	object = scene->objects;
	while (object)
	{
		if (object->type != PLANE)
		{
			object = object->next;
			continue ;
		}
		printf("Plane position: %f %f %f\n", object->pos.x, object->pos.y, object->pos.z);
		printf("Plane direction: %f %f %f\n", object->dir.x, object->dir.y, object->dir.z);
		printf("Plane radius: %f\n", object->radius);
		printf("Plane height: %f\n", object->height);
		printf("Plane color: %d %d %d\n", object->color.r, object->color.g, object->color.b);
		object = object->next;
	}
}

void print_cylinder_list(t_scene *scene)
{
	t_object *object;

	object = scene->objects;
	while (object)
	{
		if (object->type != CYLINDER)
		{
			object = object->next;
			continue ;
		}
		printf("Cylinder position: %f %f %f\n", object->pos.x, object->pos.y, object->pos.z);
		printf("Cylinder direction: %f %f %f\n", object->dir.x, object->dir.y, object->dir.z);
		printf("Cylinder radius: %f\n", object->radius);
		printf("Cylinder height: %f\n", object->height);
		printf("Cylinder color: %d %d %d\n", object->color.r, object->color.g, object->color.b);
		object = object->next;
	}
}

void	print_all(t_scene *scene)
{
	printf("Ambient light: %f\n", scene->ambient->light_ratio);
	printf("Ambient color: %d %d %d\n", scene->ambient->color.r, scene->ambient->color.g, scene->ambient->color.b);
	printf("Camera position: %f %f %f\n", scene->cam->pos.x, scene->cam->pos.y, scene->cam->pos.z);
	printf("Camera direction: %f %f %f\n", scene->cam->dir.x, scene->cam->dir.y, scene->cam->dir.z);
	printf("Camera fov: %d\n", scene->cam->fov);
	printf("Light position: %f %f %f\n", scene->light->pos.x, scene->light->pos.y, scene->light->pos.z);
	printf("Light brightness: %f\n", scene->light->brightness);
	print_sphere_list(scene);
	print_plane_list(scene);
	print_cylinder_list(scene);
}

int	main(int argc, char *argv[])
{
	t_scene			scene;

	(void) argc;
	if (ft_parsing(&scene, argv[1]) == -1)
		return (gc_dump(NULL), 0);
	if (ft_init_display(&scene.display, 800, 800, "miniRT") == -1)
		return (gc_dump(NULL), 0);
	print_all(&scene);
	printf("bpp = %d\n", scene.display.bpp);
	printf("endian mode: %s\n", scene.display.big_endian ? "big" : "little");
	mlx_hook(scene.display.window, 17, 0, close_window, &scene.display);
	mlx_hook(scene.display.window, KeyPress, KeyPressMask, key_handler, &scene);
	mlx_loop_hook(scene.display.mlx_ptr, &render_scene, &scene);
	mlx_loop(scene.display.mlx_ptr);
	return (0);
}
