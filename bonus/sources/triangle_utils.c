/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jullopez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:32:42 by jullopez          #+#    #+#             */
/*   Updated: 2024/09/18 16:32:44 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minirt.h"

bool	inside_triangle(t_object *triangle, t_vec3 *p)
{
	t_vec3	c;
	t_vec3	vp0;
	t_vec3	vp1;
	t_vec3	vp2;

	triangle->edge0 = sub_vec3(triangle->v1, triangle->v0);
	vp0 = sub_vec3(*p, triangle->v0);
	c = merge_vect(triangle->edge0, vp0);
	if (vec3_dot(&triangle->c, &c) < 0)
		return (false);
	triangle->edge1 = sub_vec3(triangle->v2, triangle->v1);
	vp1 = sub_vec3(*p, triangle->v1);
	c = merge_vect(triangle->edge1, vp1);
	if (vec3_dot(&triangle->c, &c) < 0)
		return (false);
	triangle->edge2 = sub_vec3(triangle->v0, triangle->v2);
	vp2 = sub_vec3(*p, triangle->v2);
	c = merge_vect(triangle->edge2, vp2);
	if (vec3_dot(&triangle->c, &c) < 0)
		return (false);
	return (true);
}
