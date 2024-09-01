/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:09:10 by akinzeli          #+#    #+#             */
/*   Updated: 2024/09/01 23:10:04 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

void	print_all(t_scene *scene)
{
	printf("Ambient light: %f\n", scene->ambient->light_ratio);
	printf("Ambient color: %d %d %d\n", scene->ambient->color.r, scene->ambient->color.g, scene->ambient->color.b);
	printf("Camera position: %f %f %f\n", scene->cam->pos.x, scene->cam->pos.y, scene->cam->pos.z);
	printf("Camera direction: %f %f %f\n", scene->cam->dir.x, scene->cam->dir.y, scene->cam->dir.z);
	printf("Camera fov: %d\n", scene->cam->fov);
	printf("Light position: %f %f %f\n", scene->light->pos.x, scene->light->pos.y, scene->light->pos.z);
	printf("Light brightness: %f\n", scene->light->brightness);
	print_form_list(scene);
}

void print_form_list(t_scene *scene)
{
	print_sphere_list(scene);
	print_plane_list(scene);
	print_cylinder_list(scene);
}

void print_sphere_list(t_scene *scene)
{
	t_sphere *sphere;
	int i = 1;

	sphere = scene->sphere;
	while (sphere)
	{
		printf("Sphere position %d: %f %f %f\n", i, sphere->pos.x, sphere->pos.y, sphere->pos.z);
		printf("Sphere diameter %d: %f\n", i, sphere->diameter);
		printf("Sphere color %d: %d %d %d\n", i, sphere->color.r, sphere->color.g, sphere->color.b);
		i++;
		sphere = sphere->next;
	}
}

void print_plane_list(t_scene *scene)
{
	t_plane *plane;
	int i = 1;

	plane = scene->plane;
	while (plane)
	{
		printf("Plane position %d: %f %f %f\n", i, plane->pos.x, plane->pos.y, plane->pos.z);
		printf("Plane direction %d: %f %f %f\n", i, plane->dir.x, plane->dir.y, plane->dir.z);
		printf("Plane diameter %d: %f\n", i, plane->diameter);
		printf("Plane height %d: %f\n", i, plane->height);
		printf("Plane color %d: %d %d %d\n", i, plane->color.r, plane->color.g, plane->color.b);
		plane = plane->next;
		i++;
	}
}

void print_cylinder_list(t_scene *scene)
{
	t_cylinder *cylinder;
	int i = 1;

	cylinder = scene->cylinder;
	while (cylinder)
	{
		printf("Cylinder position %d: %f %f %f\n", i, cylinder->pos.x, cylinder->pos.y, cylinder->pos.z);
		printf("Cylinder direction %d: %f %f %f\n", i, cylinder->dir.x, cylinder->dir.y, cylinder->dir.z);
		printf("Cylinder diameter %d: %f\n", i, cylinder->diameter);
		printf("Cylinder height %d: %f\n", i, cylinder->height);
		printf("Cylinder color %d: %d %d %d\n", i, cylinder->color.r, cylinder->color.g, cylinder->color.b);
		cylinder = cylinder->next;
		i++;
	}
}

void print_all_objects(t_obj *obj)
{
    while (obj)
    {
        printf("id: %d\n", obj->id);
        printf("type: %c\n", obj->type);
        printf("pos: %f %f %f\n", obj->pos.x, obj->pos.y, obj->pos.z);
        printf("dir: %f %f %f\n", obj->dir.x, obj->dir.y, obj->dir.z);
        printf("color: %d %d %d\n", obj->color.r, obj->color.g, obj->color.b);
        printf("diameter: %f\n", obj->diameter);
        printf("height: %f\n", obj->height);
        obj = obj->next;
    }
}