/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:17:11 by akinzeli          #+#    #+#             */
/*   Updated: 2024/09/09 18:15:48 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

static int	g_ids = 0;

void	add_object(t_scene *scene, t_object *object)
{
	t_object	*tmp;

	object->id = g_ids++;
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
