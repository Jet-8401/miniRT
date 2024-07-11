/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:07:55 by akinzeli          #+#    #+#             */
/*   Updated: 2024/07/11 13:48:59 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

int	add_cylinder_value(t_scene *scene, char **args)
{
	add_coordinate(args[1], &scene->cylinder->pos);
	if (add_3dvector(args[2], &scene->cylinder->dir) == -1)
		return (-1);
	add_diameter(args[3], &scene->cylinder->diameter);
	add_height(args[4], &scene->cylinder->height);
	if (add_rgb(args[5], &scene->cylinder->color) == -1)
		return (-1);
	return (0);
}

