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

#include "../header/minirt.h"

/* Note that in the sphere quadratic equation a=1.
 * Therefore every calculus have been simplified with value that
 * already has to be computed with a.
 */
bool	intersect_sphere(t_ray_view *ray, t_object *sphere, t_hit *hit)
{
	double	b;
	double	c;
	double	delta;
	t_vec3	origin;
	t_vec3	hit_point;

	vec3_subtract(&ray->origin, &sphere->pos, &origin);
	b = 2.0f * vec3_dot(&origin, &ray->direction);
	c = vec3_dot(&origin, &origin) - sphere->radius * sphere->radius;
	delta = b * b - 4.0f * c;
	if (delta < 0.0f)
		return (false);
	hit->t = (-b - sqrt(delta)) / 2.0f;
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
	t_hit	t;
	t_vec3	q;
	t_vec3	temp;

	if (intersect_cylinder_math(ray, cylinder, &t))
	{
		hit->t = t.t;
		temp = ray->direction;
		vec3_scale(&temp, t.t);
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

bool intersect_triangle(t_ray_view *ray, t_object *triangle, t_hit *hit)
{
	double	det;

	det = vec3_dot(&ray->direction, &triangle->c);
	if (fabs(det) < 1e-6)
		return (false);
	hit->t = dot(sub_vec3(triangle->v0, ray->origin), triangle->c) / det;
	if (hit->t < 0)
		return (false);
	hit->norm = triangle->c;
	vec3_normalize(&hit->norm);
	hit->hit = add_vec3(ray->origin, mult_vec3(ray->direction, hit->t));
	if (inside_triangle(triangle, &hit->hit))
		return (true);
	return (false);
}

bool inside_triangle(t_object *triangle, t_vec3 *P)
{
	t_vec3	C;
	t_vec3 vp0;
	t_vec3 vp1;
	t_vec3 vp2;

	triangle->edge0 = sub_vec3(triangle->v1, triangle->v0);
	vp0 = sub_vec3(*P, triangle->v0);
	C = merge_vect(triangle->edge0, vp0);
	if (vec3_dot(&triangle->c, &C) < 0)
		return (false);
	triangle->edge1 = sub_vec3(triangle->v2, triangle->v1);
	vp1 = sub_vec3(*P, triangle->v1);
	C = merge_vect(triangle->edge1, vp1);
	if (vec3_dot(&triangle->c, &C) < 0)
		return (false);
	triangle->edge2 = sub_vec3(triangle->v0, triangle->v2);
	vp2 = sub_vec3(*P, triangle->v2);
	C = merge_vect(triangle->edge2, vp2);
	if (vec3_dot(&triangle->c, &C) < 0)
		return (false);
	return (true);
}
