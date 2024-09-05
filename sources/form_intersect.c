/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_intersect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:06:55 by akinzeli          #+#    #+#             */
/*   Updated: 2024/09/04 22:34:34 by akinzeli         ###   ########.fr       */
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
            hit->col = plane->color;
            if (dot(hit->norm, ray->direction) > 0)
                hit->norm = mult_vec3(hit->norm, -1);
            return (true);
        }
    }
    return (false);
}

bool	intersect_cylinder(t_ray_view *ray, t_cylinder *cylinder, t_hit *hit) //t_object *cy, t_ray *ray, t_form_hit *hit)
{
    t_hit tmp_hit;
    t_vec3 q;
    int check;
    t_plane    plane;

    hit->t = INFINITY;
    plane.pos = cylinder->cap1;
    plane.dir = cylinder->dir;
    plane.color = cylinder->color;
    if (intersect_plane(ray, &plane, &tmp_hit) && distance(tmp_hit.hit, cylinder->cap1) <= cylinder->diameter * 0.5 && hit->t > tmp_hit.t)
        *hit = tmp_hit;
    plane.pos = cylinder->cap2;
    if (intersect_plane(ray, &plane, &tmp_hit) && distance(tmp_hit.hit, cylinder->cap2) <= cylinder->diameter * 0.5 && hit->t > tmp_hit.t)
        *hit = tmp_hit;
    check = 0;
    check = intersect_cylinder_math(ray, cylinder, &tmp_hit);
    if (check == 0)
        return (false);
    else if (check == 1)
    {
        hit->t = tmp_hit.t;
        hit->hit = add_vec3(ray->origin, mult_vec3(ray->direction, tmp_hit.t));
        q = sub_vec3(hit->hit, cylinder->pos);
        hit->norm = sub_vec3(q, mult_vec3(cylinder->dir, dot(cylinder->dir, q)));
        normalize_bis(&hit->norm);
        if (dot(hit->norm, ray->direction) > 0.0f)
            hit->norm = mult_vec3(hit->norm, -1);
        hit->col = cylinder->color;
        return (true);
    }
    if (hit->t < INFINITY && hit->t > EPSILON) 
        return (true);
    return (false);
    /*hit->t = tmp_hit.t;
    hit->hit = add_vec3(ray->origin, mult_vec3(ray->direction, tmp_hit.t));
    q = sub_vec3(hit->hit, cylinder->pos);
    hit->norm = sub_vec3(q, mult_vec3(cylinder->dir, dot(cylinder->dir, q)));
    normalize_bis(&hit->norm);
    if (dot(hit->norm, ray->direction) > 0.0f)
        hit->norm = mult_vec3(hit->norm, -1);
    hit->col = cylinder->color;
    return (true);*/
    
    /*t_plane    plane;
    t_hit tmp_hit;

    hit->t = INFINITY;
    plane.pos = cylinder->cap1;
    plane.dir = cylinder->dir;
    plane.color = cylinder->color;
    if (intersect_plane(ray, &plane, &tmp_hit) && distance(tmp_hit.hit, cylinder->cap1) <= cylinder->diameter * 0.5 && hit->t > tmp_hit.t)
        *hit = tmp_hit;
    plane.pos = cylinder->cap2;
    if (intersect_plane(ray, &plane, &tmp_hit) && distance(tmp_hit.hit, cylinder->cap2) <= cylinder->diameter * 0.5 && hit->t > tmp_hit.t)
        *hit = tmp_hit;
    if (infinite_cylinder(ray, cylinder, &tmp_hit) && pow(distance(cylinder->pos, tmp_hit.hit), 2) <= cylinder->height / 2 && hit->t > tmp_hit.t)
        *hit = tmp_hit;
    if (hit->t < INFINITY && hit->t > EPSILON) 
        return (true);
    return (false);*/
	/*float	a, b, c;
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
    return (true);*/
	/*vec3D_subtract(&ray->origin, &C, &X);

	a = vec3D_dot(&ray->dir, &ray->dir) - pow(vec3D_dot(&ray->dir, &cy->dir), 2);
	b = vec3D_dot(&ray->dir, &X) -
		(vec3D_dot(&ray->dir, &cy->dir) * vec3D_dot(&X, &cy->dir));
	b *= 2;
	c = vec3D_dot(&X, &X) - pow(vec3D_dot(&X, &cy->dir), 2) -
		(cy->radius * cy->radius);

	return (solve_quadratic(a, b, c));*/
}

int intersect_cylinder_math(t_ray_view *ray, t_cylinder *cylinder, t_hit *hit)
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

void check_cylinder_data(t_ray_view *ray, t_cylinder *cylinder, double *t)
{
    t_vec3 q;
    t_vec3 p2;

    p2 = add_vec3(cylinder->pos, mult_vec3(cylinder->dir, cylinder->height));
    q = add_vec3(ray->origin, mult_vec3(ray->direction, *t));
    if (dot(cylinder->dir, sub_vec3(q, cylinder->pos)) < 0 || dot(cylinder->dir, sub_vec3(q, p2)) > 0)
        *t = -1;
}

int calculation(double *t, double *t2, t_ray_view *ray, t_cylinder *cylinder)
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


/*bool infinite_cylinder(t_ray_view *ray, t_cylinder *cylinder, t_hit *hit)
{
    float	a, b, c;
	t_vec3	X = {0, 0, 0};
	t_vec3	C = {
		cylinder->pos.x - cylinder->height / 2 * ray->direction.x,
		cylinder->pos.y - cylinder->height / 2 * ray->direction.y,
		cylinder->pos.z - cylinder->height / 2 * ray->direction.z
	};
    double delta;
    double m;

	// cap1 = center - height/2 * Normal Vector

    X = sub_vec3(ray->origin, C);
    a = dot(ray->direction, ray->direction) - pow(dot(ray->direction, cylinder->dir), 2);
    b = 2 * (dot(ray->direction, X) - (dot(ray->direction, cylinder->dir) * dot(X, cylinder->dir)));
    c = dot(X, X) - pow(dot(X, cylinder->dir), 2) - (cylinder->radius * cylinder->radius);
    delta = (b * b) - 4.0f * a * c;
    if (delta < 0.0f)
        return (false);
    hit->t = (-b - sqrt(delta)) / (2.0f * a);
    hit->t2 = (-b + sqrt(delta)) / (2.0f * a);
    if (hit->t >= 0 && hit->t2 >= 0)
        hit->t = hit->t < hit->t2 ? hit->t : hit->t2;
    else if (hit->t2 >= 0)
        hit->t = hit->t2;
    hit->hit = add_vec3(ray->origin, mult_vec3(ray->direction, hit->t));
    m = dot(ray->direction, mult_vec3(cylinder->dir, hit->t)) + dot(X, cylinder->dir);
    hit->norm = sub_vec3(sub_vec3(hit->hit, cylinder->pos), mult_vec3(cylinder->dir, m));
    normalize_bis(&hit->norm);
    hit->col = cylinder->color;
    if (dot(hit->norm, ray->direction) > 0)
        hit->norm = mult_vec3(hit->norm, -1);
    return (true);
}*/

double distance(t_vec3 a, t_vec3 b)
{
    return (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2)));
}