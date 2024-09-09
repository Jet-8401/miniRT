/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_intersect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:06:55 by akinzeli          #+#    #+#             */
/*   Updated: 2024/09/09 18:00:25 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

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

bool	intersect_cylinder_math(t_ray_view *ray, t_object *cylinder, t_hit *hit)
{
	if (calculation(&hit->t, &hit->t2, ray, cylinder) == 0)
		return (0);
	if (hit->t > 0)
		check_cylinder_data(ray, cylinder, &hit->t);
	if (hit->t2 > 0)
		check_cylinder_data(ray, cylinder, &hit->t2);
	if (hit->t < 0 && hit->t2 < 0)
		return (0);
	if ((hit->t2 < hit->t && hit->t2 >= 0) || (hit->t < hit->t2 && hit->t <= 0))
		hit->t = hit->t2;
	else
		hit->t2 = hit->t;
	return (1);
}

// check the height of the cylinder
// TODO: pre-calculate the cylinder disk caps
void	check_cylinder_data(t_ray_view *ray, t_object *cylinder, double *t)
{
	t_vec3	q;
	t_vec3	p2;
	t_vec3	temp;

	p2 = cylinder->dir;
	vec3_scale(&p2, cylinder->height);
	vec3_add(&cylinder->pos, &p2, &p2);
	q = ray->direction;
	vec3_scale(&q, *t);
	vec3_add(&ray->origin, &q, &q);
	vec3_subtract(&q, &cylinder->pos, &temp);
	if (vec3_dot(&cylinder->dir, &temp) < 0)
		*t = -1;
	vec3_subtract(&q, &p2, &temp);
	if (vec3_dot(&cylinder->dir, &temp) > 0)
		*t = -1;
}

bool	calculation(double *t, double *t2, t_ray_view *ray, t_object *cylinder)
{
	t_vec3	a_sqrt;
	t_vec3	right;
	double	a;
	double	b;
	double	c;
	double	delta;
	t_vec3	origin;
	t_vec3	temp;

	temp = cylinder->dir;
	vec3_scale(&temp, vec3_dot(&ray->direction, &cylinder->dir));
	vec3_subtract(&ray->direction, &temp, &a_sqrt);
	a = vec3_dot(&a_sqrt, &a_sqrt);
	vec3_subtract(&ray->origin, &cylinder->pos, &origin);
	temp = cylinder->dir;
	vec3_scale(&temp, vec3_dot(&origin, &cylinder->dir));
	vec3_subtract(&origin, &temp, &right);
	b = 2.0f * vec3_dot(&a_sqrt, &right);
	c = vec3_dot(&right, &right) - cylinder->radius * cylinder->radius;
	delta = b * b - 4.0f * a * c;
	if (delta < 0.0f)
		return (0);
	*t = (-b - sqrt(delta)) / (2.0f * a);
	*t2 = (-b + sqrt(delta)) / (2.0f * a);
	if (*t >= 0 && *t2 >= 0)
		*t = *t < *t2 ? *t : *t2;
	else if (*t2 >= 0)
		*t = *t2;
	return (1);
}
