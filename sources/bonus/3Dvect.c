/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3Dvect.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:01:27 by akinzeli          #+#    #+#             */
/*   Updated: 2024/09/11 14:24:58 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/bonus_header/minirt.h"

// cross product
t_vec3	merge_vect(t_vec3 a, t_vec3 b)
{
	t_vec3	merged;

	merged.x = (a.y * b.z) - (a.z * b.y);
	merged.y = (a.z * b.x) - (a.x * b.z);
	merged.z = (a.x * b.y) - (a.y * b.x);
	return (merged);
}

t_vec3	*normalize_bis(t_vec3 *new)
{
	float	length;

	length = 1.0 / sqrt(new->x * new->x + new->y * new->y + new->z * new->z);
	new->x *= length;
	new->y *= length;
	new->z *= length;
	return (new);
}

t_vec3	normalize(t_vec3 new)
{
	double	length;

	length = 1.0 / sqrt(new.x * new.x + new.y * new.y + new.z * new.z);
	return ((t_vec3){new.x * length, new.y * length, new.z * length});
}

t_vec3	new_normalized(t_vec3 new)
{
	t_vec3	normalized;

	normalized = new;
	normalize_bis(&normalized);
	return (normalized);
}

double	dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
