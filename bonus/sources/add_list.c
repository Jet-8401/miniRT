/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:17:11 by akinzeli          #+#    #+#             */
/*   Updated: 2024/09/11 17:34:30 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minirt.h"

void	add_object(t_scene *scene, t_object *object)
{
	t_object	*tmp;

	tmp = scene->object;
	if (tmp == NULL)
		scene->object = object;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = object;
	}
}

void	add_light(t_scene *scene, t_light *light)
{
	t_light	*tmp;

	tmp = scene->light;
	if (tmp == NULL)
		scene->light = light;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = light;
	}
}
