/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:17:22 by jullopez          #+#    #+#             */
/*   Updated: 2024/09/11 12:59:51 by akinzeli         ###   ########.fr       */
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
	t_equation	eq;
	t_vec3		a_sqrt;
	t_vec3		right;

	eq.temp = cylinder->dir;
	vec3_scale(&eq.temp, vec3_dot(&ray->direction, &cylinder->dir));
	vec3_subtract(&ray->direction, &eq.temp, &a_sqrt);
	eq.a = vec3_dot(&a_sqrt, &a_sqrt);
	vec3_subtract(&ray->origin, &cylinder->pos, &eq.origin);
	eq.temp = cylinder->dir;
	vec3_scale(&eq.temp, vec3_dot(&eq.origin, &cylinder->dir));
	vec3_subtract(&eq.origin, &eq.temp, &right);
	eq.b = 2.0f * vec3_dot(&a_sqrt, &right);
	eq.c = vec3_dot(&right, &right) - cylinder->radius * cylinder->radius;
	eq.delta = eq.b * eq.b - 4.0f * eq.a * eq.c;
	if (eq.delta < 0.0f)
		return (0);
	solve_calculation(&t, &t2, &eq);
	return (1);
}

void	solve_calculation(double **t, double **t2, t_equation *eq)
{
	*(*t) = (-eq->b - sqrt(eq->delta)) / (2.0f * eq->a);
	*(*t2) = (-eq->b + sqrt(eq->delta)) / (2.0f * eq->a);
	if (*(*t) >= 0 && *(*t2) >= 0)
	{
		if (*(*t) >= *(*t2))
			*(*t) = *(*t2);
	}
	else if (*(*t2) >= 0)
		*(*t) = *(*t2);
}
