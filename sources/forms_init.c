/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forms_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:52:05 by jullopez          #+#    #+#             */
/*   Updated: 2024/07/11 15:52:28 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

int	sphere_init(t_scene *scene, char **args)
{
	t_sphere *sphere;

	sphere = gc_malloc(sizeof(t_sphere));
	scene->sphere = sphere;
	if (ft_strlen2(args) != 4)
		return (ft_err("Bad arguments number sphere", 0), -1);
	if (check_coordinate(args[1]) == -1)
		return (ft_err("Bad argument coordinate sphere", 0), -1);
	if (check_HD(args[2]) == -1)
		return (ft_err("Bad height sphere", 0), -1);
	if (check_rgb(args[3]) == -1)
		return (ft_err("Bad rgb arguments sphere", 0), -1);
	if (add_sphere_value(scene, args) == -1)
		return (ft_err("Wrong sphere values", 0), -1);
	return (0);
}

int	plane_init(t_scene *scene, char **args)
{
	t_plane *plane;

	plane = gc_malloc(sizeof(t_plane));
	scene->plane = plane;
	if (ft_strlen2(args) != 4)
		return (ft_err("Bad arguments number plane", 0), -1);
	if (check_coordinate(args[1]) == -1)
		return (ft_err("Bad argument coordinate sphere", 0), -1);
	if (check_3d_vector(args[2]) == -1)
		return (ft_err("Bad 3d vector plane", 0), -1);
	if (check_rgb(args[3]) == -1)
		return (ft_err("Bad rgb plane", 0), -1);
	if (add_plane_value(scene, args) == -1)
		return (ft_err("wrong plane values", 0), -1);
	return (0);
}

int	cylinder_init(t_scene *scene, char **args)
{
	t_cylinder *cylinder;

	cylinder = gc_malloc(sizeof(t_cylinder));
	scene->cylinder = cylinder;
	if (ft_strlen2(args) != 6)
		return (ft_err("Bad arguments number cylinder", 0), -1);
	if (check_coordinate(args[1]) == -1)
		return (ft_err("Bad coordinate cylinder", 0), -1);
	if (check_3d_vector(args[2]) == -1)
		return (ft_err("Bad 3d vector cylinder", 0), -1);
	if (check_HD(args[3]) == -1)
		return (ft_err("Bad diameter", 0), -1);
	if (check_HD(args[4]) == -1)
		return (ft_err("Bad height cylinder", 0), -1);
	if (check_rgb(args[5]) == -1)
		return (ft_err("Bad rgb cylinder", 0), -1);
	if (add_cylinder_value(scene, args) == -1)
		return (ft_err("wrong cylinder values", 0), -1);
	return (0);
}
