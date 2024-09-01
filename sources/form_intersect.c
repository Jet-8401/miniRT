/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_intersect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:06:55 by akinzeli          #+#    #+#             */
/*   Updated: 2024/09/01 23:58:36 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

bool intersect_sphere(t_ray_view *ray, t_sphere *sphere, t_hit *hit)
{
    double a;
    double b;
    double c;
    double delta;

    a = dot(ray->direction, ray->direction);
    b = 2.0f * dot(sub_vec3(ray->origin, sphere->pos), ray->direction);
    c = dot(sub_vec3(ray->origin, sphere->pos), sub_vec3(ray->origin, sphere->pos)) - sphere->radius * sphere->radius;
    delta = b * b - 4.0f * a * c;
    if (delta >= 0.0f)
    {
        hit->t = (-b - sqrt(delta)) / (2.0f * a);
        hit->hit = add_vec3(ray->origin, mult_vec3(ray->direction, hit->t));
        hit->norm = sub_vec3(hit->hit, sphere->pos);
        normalize_bis(&hit->norm);
        hit->col = sphere->color;
        return (true);
    }
    return (false);
}

bool intersect_plane(t_ray_view *ray, t_plane *plane, t_hit *hit)
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

bool	intersect_cylinder(t_ray_view *ray, t_cylinder *cylinder, t_hit *hit) //t_object *cy, t_ray *ray, t_form_hit *hit)
{
	float	a, b, c;
	t_vec3	X = {0, 0, 0};
	t_vec3	C = {
		cylinder->pos.x - cylinder->height / 2 * ray->direction.x,
		cylinder->pos.y - cylinder->height / 2 * ray->direction.y,
		cylinder->pos.z - cylinder->height / 2 * ray->direction.z
	};

	// cap1 = center - height/2 * Normal Vector

    X = sub_vec3(ray->origin, C);
    a = dot(ray->direction, ray->direction) - pow(dot(ray->direction, cylinder->dir), 2);
    b = 2 * (dot(ray->direction, X) - (dot(ray->direction, cylinder->dir) * dot(X, cylinder->dir)));
    c = dot(X, X) - pow(dot(X, cylinder->dir), 2) - (cylinder->radius * cylinder->radius);
    hit->t = (b * b) - 4.0f * a * c;
    if (hit->t < 0.0f)
        return (false);
    hit->t = (-b - sqrt(hit->t)) / (2.0f * a);
    hit->hit = add_vec3(ray->origin, mult_vec3(ray->direction, hit->t));
    hit->norm = sub_vec3(hit->hit, C);
    normalize_bis(&hit->norm);
    hit->col = cylinder->color;
    return (true);
	/*vec3D_subtract(&ray->origin, &C, &X);

	a = vec3D_dot(&ray->dir, &ray->dir) - pow(vec3D_dot(&ray->dir, &cy->dir), 2);
	b = vec3D_dot(&ray->dir, &X) -
		(vec3D_dot(&ray->dir, &cy->dir) * vec3D_dot(&X, &cy->dir));
	b *= 2;
	c = vec3D_dot(&X, &X) - pow(vec3D_dot(&X, &cy->dir), 2) -
		(cy->radius * cy->radius);

	return (solve_quadratic(a, b, c));*/
}