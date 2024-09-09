/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jullopez <jullopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:17:22 by jullopez          #+#    #+#             */
/*   Updated: 2024/09/09 19:17:23 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

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
