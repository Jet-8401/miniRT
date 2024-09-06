/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:07:52 by akinzeli          #+#    #+#             */
/*   Updated: 2024/09/03 22:56:29 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

bool	intersect(t_render *render, t_object *obj, t_hit *hit)
{
	float			closest_distance;
	bool			has_hit;

	closest_distance = 3.402823466e+38F;
	has_hit = 0;
	while (obj)
	{
		if (new_intersect(render, obj, hit) && hit->t < closest_distance)
		{
			has_hit = 1;
			closest_distance = hit->t;
			hit->object = obj;
		}
		obj = obj->next;
	}
	return (has_hit);
}

bool intersect_shadow(t_render *render, t_scene *scene, t_hit *hit)
{
    double		max_distance;
    t_hit		tmp_hit;
    t_object	*obj;

    max_distance = render->light_distance;
    tmp_hit.t = INFINITY;
    obj = scene->object;
    while (obj)
    {
        if (obj->id != hit->object->id)
        {
        	if(new_intersect(render, obj, &tmp_hit) && tmp_hit.t < max_distance && tmp_hit.t > 0.0f)
                return (true);
        }
        obj = obj->next;
    }
    return (false);
}

int new_intersect(t_render *render, t_object *obj, t_hit *hit)
{
    if (obj->type == SPHERE)
        return (intersect_sphere(&render->prime_ray, obj, hit));
    else if (obj->type == PLANE)
        return (intersect_plane(&render->prime_ray, obj, hit));
    else if (obj->type == CYLINDER)
        return (intersect_cylinder(&render->prime_ray, obj, hit));
    return (0);
}
