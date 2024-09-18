/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_intersect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:06:55 by akinzeli          #+#    #+#             */
/*   Updated: 2024/09/12 14:31:23 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

/* Note that in the sphere quadratic equation a=1.
 * Therefore every calculus have been simplified with value that
 * already has to be computed with a.
 */
bool	intersect_sphere(t_ray_view *ray, t_object *sphere, t_hit *hit)
{
	t_vec3	origin;
	t_vec3	hit_point;

	vec3_subtract(&ray->origin, &sphere->pos, &origin);
	hit->eq.b = 2.0f * vec3_dot(&origin, &ray->direction);
	hit->eq.c = vec3_dot(&origin, &origin) - sphere->radius * sphere->radius;
	hit->eq.delta = hit->eq.b * hit->eq.b - 4.0f * hit->eq.c;
	if (hit->eq.delta < 0.0f)
		return (false);
	hit->t = (-hit->eq.b - sqrt(hit->eq.delta)) / 2.0f;
	hit->t2 = (-hit->eq.b + sqrt(hit->eq.delta)) / 2.0f;
	if (hit->t < 0.0f && hit->t2 < 0.0f)
		return (false);
	if (hit->t < 0.0f)
		hit->t = hit->t2;
	hit_point = ray->direction;
	vec3_scale(&hit_point, hit->t);
	vec3_add(&hit_point, &ray->origin, &hit->hit);
	vec3_subtract(&hit->hit, &sphere->pos, &hit->norm);
	vec3_normalize(&hit->norm);
	return (true);
}

bool	intersect_plane(t_ray_view *ray, t_object *plane, t_hit *hit)
{
	double	denom;
	t_vec3	origin;
	t_vec3	hit_point;

	denom = vec3_dot(&plane->dir, &ray->direction);
	if (fabs(denom) > 1e-6)
	{
		vec3_subtract(&plane->pos, &ray->origin, &origin);
		hit->t = vec3_dot(&origin, &plane->dir) / denom;
		if (hit->t < 0.0f)
			return (false);
		hit_point = ray->direction;
		vec3_scale(&hit_point, hit->t);
		vec3_add(&ray->origin, &hit_point, &hit->hit);
		hit->norm = plane->dir;
		if (vec3_dot(&hit->norm, &ray->direction) > 0)
			vec3_scale(&hit->norm, -1);
		return (true);
	}
	return (false);
}

bool	intersect_disk(t_ray_view *ray, t_object *disk, t_hit *hit)
{
	t_vec3	v;
	float	d;

	if (!intersect_plane(ray, disk, hit))
		return (false);
	vec3_subtract(&hit->hit, &disk->pos, &v);
	d = vec3_dot(&v, &v);
	if (d > disk->radius * disk->radius)
		return (false);
	hit->norm = disk->dir;
	return (true);
}

bool	intersect_cylinder(t_ray_view *ray, t_object *cylinder, t_hit *hit)
{
	t_vec3	q;
	t_vec3	temp;

	if (intersect_cylinder_math(ray, cylinder, hit))
	{
		temp = ray->direction;
		vec3_scale(&temp, hit->t);
		vec3_add(&ray->origin, &temp, &hit->hit);
		vec3_subtract(&hit->hit, &cylinder->pos, &q);
		temp = cylinder->dir;
		vec3_scale(&temp, vec3_dot(&cylinder->dir, &q));
		vec3_subtract(&q, &temp, &hit->norm);
		vec3_normalize(&hit->norm);
		if (vec3_dot(&hit->norm, &ray->direction) > 0)
			vec3_scale(&hit->norm, -1);
		return (true);
	}
	return (false);
}
