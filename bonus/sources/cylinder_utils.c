/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:17:22 by jullopez          #+#    #+#             */
/*   Updated: 2024/09/11 16:24:56 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minirt.h"

// check the height of the cylinder
static void	check_cylinder_height(t_ray_view *ray, t_object *cylinder, double *t)
{
	t_vec3	q;
	t_vec3	temp;

	q = ray->direction;
	vec3_scale(&q, *t);
	vec3_add(&ray->origin, &q, &q);
	vec3_subtract(&q, &cylinder->pos, &temp);
	if (vec3_dot(&cylinder->dir, &temp) < 0)
		*t = -1;
	vec3_subtract(&q, &cylinder->end_cap->pos, &temp);
	if (vec3_dot(&cylinder->dir, &temp) > 0)
		*t = -1;
}

static void	solve_calculation(double *t, double *t2, t_equation *eq)
{
	*t = (-eq->b - sqrt(eq->delta)) / (2.0f * eq->a);
	*t2 = (-eq->b + sqrt(eq->delta)) / (2.0f * eq->a);
	if (*t > 0.0f && *t2 > 0.0f)
		return ;
	if (*t > *t2)
		*t = *t2;
	return ;
}

static bool	calculation(t_hit *hit, t_ray_view *ray, t_object *cylinder)
{
	t_vec3		a_sqrt;
	t_vec3		right;

	hit->eq.temp = cylinder->dir;
	vec3_scale(&hit->eq.temp, vec3_dot(&ray->direction, &cylinder->dir));
	vec3_subtract(&ray->direction, &hit->eq.temp, &a_sqrt);
	hit->eq.a = vec3_dot(&a_sqrt, &a_sqrt);
	vec3_subtract(&ray->origin, &cylinder->pos, &hit->eq.origin);
	hit->eq.temp = cylinder->dir;
	vec3_scale(&hit->eq.temp, vec3_dot(&hit->eq.origin, &cylinder->dir));
	vec3_subtract(&hit->eq.origin, &hit->eq.temp, &right);
	hit->eq.b = 2.0f * vec3_dot(&a_sqrt, &right);
	hit->eq.c = vec3_dot(&right, &right) - cylinder->radius * cylinder->radius;
	hit->eq.delta = hit->eq.b * hit->eq.b - 4.0f * hit->eq.a * hit->eq.c;
	if (hit->eq.delta < 0.0f)
		return (0);
	solve_calculation(&hit->t, &hit->t2, &hit->eq);
	return (1);
}

bool	intersect_cylinder_math(t_ray_view *ray, t_object *cylinder, t_hit *hit)
{
	if (calculation(hit, ray, cylinder) == 0)
		return (0);
	if (hit->t > 0)
		check_cylinder_height(ray, cylinder, &hit->t);
	if (hit->t2 > 0)
		check_cylinder_height(ray, cylinder, &hit->t2);
	if (hit->t < 0 && hit->t2 < 0)
		return (0);
	if ((hit->t2 < hit->t && hit->t2 >= 0) || (hit->t < hit->t2 && hit->t <= 0))
		hit->t = hit->t2;
	return (1);
}
