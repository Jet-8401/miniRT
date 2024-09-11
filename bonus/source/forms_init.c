/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forms_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:52:05 by jullopez          #+#    #+#             */
/*   Updated: 2024/09/11 16:24:56 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minirt.h"

int	light_init(t_scene *scene, char **args)
{
	t_light	*light;

	light = gc_calloc(sizeof(t_light));
	if (!light)
		return (-1);
	if (ft_strlen2(args) != 4)
		return (ft_err("Bad arguments number light", 0), -1);
	if (set_vector3d(&light->pos, args[1]) == -1)
		return (ft_err("Bad coordinate light", 0), -1);
	if (set_ratio(args[2], &light->brightness) == -1)
		return (ft_err("Bad light ratio", 0), -1);
	scene->light = light;
	return (0);
}

int	sphere_init(t_scene *scene, char **args)
{
	t_object	*sphere;

	sphere = gc_calloc(sizeof(t_object));
	if (!sphere)
		return (-1);
	if (ft_strlen2(args) != 4)
		return (ft_err("Bad arguments number sphere", 0), -1);
	if (set_vector3d(&sphere->pos, args[1]) == -1)
		return (ft_err("Bad argument coordinate sphere", 0), -1);
	if (set_float_value(args[2], &sphere->diameter) == -1)
		return (ft_err("Bad height sphere", 0), -1);
	if (set_rgb(args[3], &sphere->color) == -1)
		return (ft_err("Bad rgb arguments sphere", 0), -1);
	sphere->radius = sphere->diameter / 2;
	sphere->type = SPHERE;
	add_object(scene, sphere);
	return (0);
}

int	plane_init(t_scene *scene, char **args)
{
	t_object	*plane;

	plane = gc_calloc(sizeof(t_object));
	if (!plane)
		return (-1);
	if (ft_strlen2(args) != 4)
		return (ft_err("Bad arguments number plane", 0), -1);
	if (set_vector3d(&plane->pos, args[1]) == -1)
		return (ft_err("Bad argument coordinate sphere", 0), -1);
	if (set_normalized_vector3d(&plane->dir, args[2]) == -1)
		return (ft_err("Bad 3d vector plane", 0), -1);
	if (set_rgb(args[3], &plane->color) == -1)
		return (ft_err("Bad rgb plane", 0), -1);
	plane->type = PLANE;
	vec3_normalize(&plane->dir);
	add_object(scene, plane);
	return (0);
}

void	cylinder_disk_init(t_scene *scene, t_object *cylinder)
{
	t_object	*cap[2];
	t_vec3		temp;
	int			i;

	i = -1;
	while (++i < 2)
	{
		cap[i] = gc_calloc(sizeof(t_object));
		*cap[i] = *cylinder;
		cap[i]->type = DISK;
	}
	temp = cylinder->dir;
	vec3_scale(&temp, cylinder->height);
	vec3_add(&cylinder->pos, &temp, &cap[1]->pos);
	cylinder->start_cap = cap[0];
	cylinder->end_cap = cap[1];
	add_object(scene, cap[0]);
	add_object(scene, cap[1]);
}

int	cylinder_init(t_scene *scene, char **args)
{
	t_object	*cylinder;

	cylinder = gc_calloc(sizeof(t_object));
	if (!cylinder)
		return (-1);
	if (ft_strlen2(args) != 6)
		return (ft_err("Bad arguments number cylinder", 0), -1);
	if (set_vector3d(&cylinder->pos, args[1]) == -1)
		return (ft_err("Bad coordinate cylinder", 0), -1);
	if (set_normalized_vector3d(&cylinder->dir, args[2]) == -1)
		return (ft_err("Bad 3d vector cylinder", 0), -1);
	if (set_float_value(args[3], &cylinder->diameter) == -1)
		return (ft_err("Bad diameter", 0), -1);
	if (set_float_value(args[4], &cylinder->height) == -1)
		return (ft_err("Bad height cylinder", 0), -1);
	if (set_rgb(args[5], &cylinder->color) == -1)
		return (ft_err("Bad rgb cylinder", 0), -1);
	cylinder->radius = cylinder->diameter / 2;
	cylinder->type = CYLINDER;
	vec3_normalize(&cylinder->dir);
	cylinder_disk_init(scene, cylinder);
	add_object(scene, cylinder);
	return (0);
}
