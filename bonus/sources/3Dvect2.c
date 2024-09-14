/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3Dvect2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:03:10 by akinzeli          #+#    #+#             */
/*   Updated: 2024/09/11 16:25:08 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minirt.h"

t_vec3	sub_vec3(t_vec3 a, t_vec3 b)
{
	t_vec3	sub;

	sub.x = a.x - b.x;
	sub.y = a.y - b.y;
	sub.z = a.z - b.z;
	return (sub);
}

t_vec3	mult_vec3(t_vec3 a, double b)
{
	t_vec3	mult;

	mult.x = a.x * b;
	mult.y = a.y * b;
	mult.z = a.z * b;
	return (mult);
}

t_vec3	add_vec3(t_vec3 a, t_vec3 b)
{
	t_vec3	added;

	added.x = a.x + b.x;
	added.y = a.y + b.y;
	added.z = a.z + b.z;
	return (added);
}

double	vec3_length(t_vec3 vec)
{
	return (sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2)));
}
