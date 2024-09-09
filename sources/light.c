/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:13:27 by akinzeli          #+#    #+#             */
/*   Updated: 2024/09/09 17:36:28 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

t_rgb ambiant_color(t_render *render, t_scene *scene)
{
    t_rgb color;
    t_hit hit;

    ft_memset(&color, 0, sizeof(t_rgb));
    if (!intersect(render, scene->object, &hit))
    	return (color);
    color = light_handler(scene, render, &hit);
    //color = hit.object->color;
    return (color);
}

t_rgb light_handler(t_scene *scene, t_render *render, t_hit *hit)
{
    double d;

    render->ambiant_light = vect_to_rgb(vec3_ambiant(hit->object->color, scene->ambient->color, scene->ambient->light_ratio));
    if (scene->light != NULL)
    {
        if (dot(hit->norm, render->prime_ray.direction) > 0)
            hit->norm = mult_vec3(hit->norm, -1);
        d = dot(hit->norm, new_normalized(sub_vec3(scene->light->pos, hit->hit)));
        if (d < 0)
            d = 0;
        render->color = vect_to_rgb(vec3_ambiant(hit->object->color, (t_rgb){255, 255, 255}, d * scene->light->brightness));
        if (new_shadow_ray(scene, hit, render))
            render->color = mult_rgb(render->color, scene->ambient->light_ratio);
        //render->color = add_rgb(render->color, render->ambiant_light);
    }
    return (add_rgb(render->color, render->ambiant_light));
}

bool new_shadow_ray(t_scene *scene, t_hit *hit, t_render *render)
{
    t_vec3 light_dir;
    t_light *new_light;
    t_ray_view ray;

    new_light = scene->light;
    light_dir = sub_vec3(new_light->pos, hit->hit);
    render->light_distance = vec3_length(light_dir);
    ray.origin = hit->hit;
    ray.direction = new_normalized(light_dir);
    render->prime_ray = ray;
    return (intersect_shadow(render, scene, hit));
}
