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
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

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

	sphere = scene->sphere;
	while (sphere)
	{
		printf("Sphere position: %f %f %f\n", sphere->pos.x, sphere->pos.y, sphere->pos.z);
		printf("Sphere diameter: %f\n", sphere->diameter);
		printf("Sphere color: %d %d %d\n", sphere->color.r, sphere->color.g, sphere->color.b);
		sphere = sphere->next;
	}
}

void print_plane_list(t_scene *scene)
{
	t_plane *plane;

	plane = scene->plane;
	while (plane)
	{
		printf("Plane position: %f %f %f\n", plane->pos.x, plane->pos.y, plane->pos.z);
		printf("Plane direction: %f %f %f\n", plane->dir.x, plane->dir.y, plane->dir.z);
		printf("Plane diameter: %f\n", plane->diameter);
		printf("Plane height: %f\n", plane->height);
		printf("Plane color: %d %d %d\n", plane->color.r, plane->color.g, plane->color.b);
		plane = plane->next;
	}
}

void print_cylinder_list(t_scene *scene)
{
	t_cylinder *cylinder;

	cylinder = scene->cylinder;
	while (cylinder)
	{
		printf("Cylinder position: %f %f %f\n", cylinder->pos.x, cylinder->pos.y, cylinder->pos.z);
		printf("Cylinder direction: %f %f %f\n", cylinder->dir.x, cylinder->dir.y, cylinder->dir.z);
		printf("Cylinder diameter: %f\n", cylinder->diameter);
		printf("Cylinder height: %f\n", cylinder->height);
		printf("Cylinder color: %d %d %d\n", cylinder->color.r, cylinder->color.g, cylinder->color.b);
		cylinder = cylinder->next;
	}
}

int	render_scene(t_display *display)
{
	static uint32_t	red;
	static uint32_t	green;

	for(int y = 0; y < display->height; y++) {
		for (int x = 0; x < display->width; x++) {
			red = (uint8_t)((x / (float) display->width) * 255);
			green = (uint8_t)((y / (float) display->height) * 255);
			display->data[x + y * display->width] = red << 16 | green << 8;
		}
	}
	mlx_put_image_to_window(display->mlx_ptr, display->window,
		display->render_img, 0, 0);
	fps_display(display);
	//usleep(500000);
	//sleep(1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_scene			scene;
	t_display		display;

	(void) argc;
	if (ft_parsing(&scene, argv[1]) == -1)
		return (gc_dump(NULL), 0);
	if (ft_init_display(&display, 800, 800, "miniRT") == -1)
		return (gc_dump(NULL), 0);
	print_all(&scene);
	printf("bpp = %d\n", display.bpp);
	printf("endian mode: %s\n", display.big_endian ? "big" : "little");
	mlx_loop_hook(display.mlx_ptr, &render_scene, &display);
	mlx_loop(display.mlx_ptr);
	return (0);
}
