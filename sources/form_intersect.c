/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_intersect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:06:55 by akinzeli          #+#    #+#             */
/*   Updated: 2024/09/05 20:11:46 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

bool intersect_sphere(t_ray_view *ray, t_object *sphere, t_hit *hit)
{
    double a;
    double b;
    double c;
    double delta;

    a = 1; //dot(ray->direction, ray->direction);
    b = 2.0f * dot(sub_vec3(ray->origin, sphere->pos), ray->direction);
    c = dot(sub_vec3(ray->origin, sphere->pos), sub_vec3(ray->origin, sphere->pos)) - sphere->radius * sphere->radius;
    delta = b * b - 4.0f * a * c;
    if (delta >= 0.0f)
    {
        hit->t = (-b - sqrt(delta)) / (2.0f * a);
        hit->hit = add_vec3(ray->origin, mult_vec3(ray->direction, hit->t));
        hit->norm = sub_vec3(hit->hit, sphere->pos);
        normalize_bis(&hit->norm);
        return (true);
    }
    return (false);
}

bool intersect_plane(t_ray_view *ray, t_object *plane, t_hit *hit)
{
    double denom;

    denom = dot(plane->dir, ray->direction);
    if (fabs(denom) > 1e-6)
    {
        hit->t = dot(sub_vec3(plane->pos, ray->origin), plane->dir) / denom;
        if (hit->t >= 0)
        {
            hit->hit = add_vec3(ray->origin, mult_vec3(ray->direction, hit->t));
            hit->norm = plane->dir;
            if (dot(hit->norm, ray->direction) > 0)
                hit->norm = mult_vec3(hit->norm, -1);
            return (true);
        }
    }
    return (false);
}

bool	intersect_disk(t_ray_view *ray, t_object *plane, t_hit *hit,
	float radius)
{
	t_vec3	v;
	float	d;

	if (!intersect_plane(ray, plane, hit))
		return (false);
	v = sub_vec3(hit->hit, plane->pos);
	d = dot(v, v);
	if (d > radius * radius)
		return (false);
	hit->norm = plane->dir;
	return (true);
}

/*
// check if disk are in closer
if (intersect_disk(ray, &cylinder->cap2, &tmp_hit, cylinder->radius))
	return (*hit = tmp_hit, true);
if (intersect_disk(ray, &cylinder->cap1, &tmp_hit, cylinder->radius))
	return (*hit = tmp_hit, true);
   return (false);
*/

//t_object *cy, t_ray *ray, t_form_hit *hit)
bool	intersect_cylinder(t_ray_view *ray, t_object *cylinder, t_hit *hit)
{
    t_hit	t;
    t_vec3	q;

    if (intersect_cylinder_math(ray, cylinder, &t))
    {
        hit->t = t.t;
        hit->hit = add_vec3(ray->origin, mult_vec3(ray->direction, t.t));
        q = sub_vec3(hit->hit, cylinder->pos);
        hit->norm = sub_vec3(q, mult_vec3(cylinder->dir, dot(cylinder->dir, q)));
        normalize_bis(&hit->norm);
        if (dot(hit->norm, ray->direction) > 0.0f)
            hit->norm = mult_vec3(hit->norm, -1);
        return (true);
    }
    return (false);
}

int intersect_cylinder_math(t_ray_view *ray, t_object *cylinder, t_hit *hit)
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

void check_cylinder_data(t_ray_view *ray, t_object *cylinder, double *t)
{
    t_vec3 q;
    t_vec3 p2;

    p2 = add_vec3(cylinder->pos, mult_vec3(cylinder->dir, cylinder->height));
    q = add_vec3(ray->origin, mult_vec3(ray->direction, *t));
    if (dot(cylinder->dir, sub_vec3(q, cylinder->pos)) < 0 || dot(cylinder->dir, sub_vec3(q, p2)) > 0)
        *t = -1;
}

int calculation(double *t, double *t2, t_ray_view *ray, t_object *cylinder)
{
    t_vec3 a_sqrt;
    t_vec3 right;
    double a;
    double b;
    double c;
    double delta;

    a_sqrt = sub_vec3(ray->direction, mult_vec3(cylinder->dir, dot(ray->direction, cylinder->dir)));
    a = dot(a_sqrt, a_sqrt);
    right = sub_vec3(sub_vec3(ray->origin, cylinder->pos), mult_vec3(cylinder->dir, dot(sub_vec3(ray->origin, cylinder->pos), cylinder->dir)));
    b = 2.0f * dot(a_sqrt, right);
    c = dot(right, right) - cylinder->radius * cylinder->radius;
    delta = b * b - 4.0f * a * c;
    if (delta < 0.0f)
        return (0);
    else if (delta == 0.0f)
    {
        *t = -b / (2.0f * a);
        *t2 = -b / (2.0f * a);
    }
    else
    {
        *t = (-b - sqrt(delta)) / (2.0f * a);
        *t2 = (-b + sqrt(delta)) / (2.0f * a);
    }
    if (*t >= 0 && *t2 >= 0)
        *t = *t < *t2 ? *t : *t2;
    else if (*t2 >= 0)
        *t = *t2;
    return (1);
}

double distance(t_vec3 a, t_vec3 b)
{
    return (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2)));
}
