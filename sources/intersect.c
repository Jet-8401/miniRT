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

t_obj *intersect(t_render *render, t_obj *obj, t_hit *hit)
{
    double min_distance;
    t_obj *obj_closest;
    t_hit tmp_hit;

    min_distance = INFINITY;
    tmp_hit.t = 0;
    obj_closest = NULL;
    while (obj)
    {
        if (new_intersect(render, obj, &tmp_hit))
        {
            if (tmp_hit.t < min_distance)
            {
                min_distance = tmp_hit.t;
                obj_closest = obj;
                *hit = tmp_hit;
            }
        }
        obj = obj->next;
    }
    if (obj_closest)
        hit->col = obj_closest->color;
    return (obj_closest);
}

bool intersect_shadow(t_render *render, t_scene *scene)
{
    double max_distance;
    t_hit tmp_hit;
    t_obj *obj;

    max_distance = render->light_distance;
    tmp_hit.t = INFINITY;
    obj = scene->obj;
    while (obj)
    {
        if (obj->id != render->obj_closest->id)
        {        
            if(new_intersect(render, obj, &tmp_hit) && tmp_hit.t < max_distance && tmp_hit.t > 0.0f)
                return (true);
        }
        obj = obj->next;
    }
    return (false);
}

int new_intersect(t_render *render, t_obj *obj, t_hit *hit)
{
    if (obj->type == 's')
        return (intersect_sphere(&render->prime_ray, &obj->object.sphere, hit));
    else if (obj->type == 'p')
        return (intersect_plane(&render->prime_ray, &obj->object.plane, hit));
    else if (obj->type == 'c')
        return (intersect_cylinder(&render->prime_ray, &obj->object.cylinder, hit));
    return (0);
}

