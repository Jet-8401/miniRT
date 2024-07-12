/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:17:11 by akinzeli          #+#    #+#             */
/*   Updated: 2024/07/12 13:19:32 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

void	add_sphere(t_scene *scene, t_sphere *new)
{
	t_sphere	*tmp;

	tmp = scene->sphere;
	if (tmp == NULL)
		scene->sphere = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	add_plane(t_scene *scene, t_plane *new)
{
	t_plane	*tmp;

	tmp = scene->plane;
	if (tmp == NULL)
		scene->plane = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	add_cylinder(t_scene *scene, t_cylinder *new)
{
	t_cylinder *tmp;

	tmp = scene->cylinder;
	if (tmp == NULL)
		scene->cylinder = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}