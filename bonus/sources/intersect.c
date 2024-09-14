/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:07:52 by akinzeli          #+#    #+#             */
/*   Updated: 2024/09/11 16:24:56 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minirt.h"

bool	intersect(t_render *render, t_object *obj, t_hit *hit)
{
	bool	has_hit;
	t_hit	tmp;

	hit->t = 3.402823466e+38f;
	has_hit = 0;
	while (obj)
	{
		if (does_intersect(render, obj, &tmp) && tmp.t < hit->t)
		{
			has_hit = 1;
			*hit = tmp;
			hit->object = obj;
		}
		obj = obj->next;
	}
	return (has_hit);
}

bool	intersect_shadow(t_render *render, t_scene *scene, t_hit *hit)
{
	double		max_distance;
	t_hit		tmp_hit;
	t_object	*obj;

	max_distance = render->light_distance;
	tmp_hit.t = INFINITY;
	obj = scene->object;
	while (obj)
	{
		if (obj != hit->object)
		{
			if (does_intersect(render, obj, &tmp_hit)
				&& tmp_hit.t < max_distance && tmp_hit.t > 0.0f)
				return (true);
		}
		obj = obj->next;
	}
	return (false);
}

bool	does_intersect(t_render *render, t_object *obj, t_hit *hit)
{
	static bool	(*intersections[5])(t_ray_view*, t_object*, t_hit*) = {
		intersect_sphere, intersect_plane, intersect_cylinder, intersect_disk, intersect_triangle
	};

	return (intersections[obj->type](&render->prime_ray, obj, hit));
}
