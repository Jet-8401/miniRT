/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:13:27 by akinzeli          #+#    #+#             */
/*   Updated: 2024/09/12 14:43:49 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minirt.h"

t_rgb	ambiant_color(t_render *render, t_scene *scene)
{
	t_rgb	color;
	t_hit	hit;

	ft_memset(&color, 0, sizeof(t_rgb));
	if (!intersect(render, scene->object, &hit))
		return (color);
	color = light_handler(scene, render, &hit);
	return (color);
}

t_rgb	light_handler(t_scene *scene, t_render *render, t_hit *hit)
{
	double	d;
	t_light	*tmp_light;
	t_rgb tmp_color;

	tmp_light = scene->light;
	render->ambiant_light = vect_to_rgb(vec3_ambiant(hit->object->color,
				scene->ambient->color, scene->ambient->light_ratio));
	if (tmp_light != NULL)
	{
		while (tmp_light)
		{
			if (dot(hit->norm, render->prime_ray.direction) > 0)
				hit->norm = mult_vec3(hit->norm, -1);
			d = dot(hit->norm, new_normalized(sub_vec3(tmp_light->pos,
							hit->hit)));
			if (d < 0)
				d = 0;
			tmp_color = vect_to_rgb(vec3_ambiant(hit->object->color,
						tmp_light->color, d * tmp_light->brightness));
			if (new_shadow_ray(scene, hit, render))
				tmp_color = mult_rgb(tmp_color,
						scene->ambient->light_ratio);
			tmp_color = add_rgb(tmp_color, render->ambiant_light);
			render->color = tmp_color;
			tmp_light = tmp_light->next;
		}
	}
	return (render->color);
}

bool	new_shadow_ray(t_scene *scene, t_hit *hit, t_render *render)
{
	t_light		*new_light;
	t_vec3		light_dir;
	t_ray_view	ray;

	new_light = scene->light;
	light_dir = sub_vec3(new_light->pos, hit->hit);
	render->light_distance = vec3_length(light_dir);
	ray.origin = hit->hit;
	ray.direction = new_normalized(light_dir);
	render->prime_ray = ray;
	return (intersect_shadow(render, scene, hit));
}
