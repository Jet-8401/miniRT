/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_vect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:04:49 by akinzeli          #+#    #+#             */
/*   Updated: 2024/09/09 18:00:15 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

t_rgb	mult_color_vec4(t_rgb color, t_rgb color2)
{
	t_rgb	mult;

	mult.r = check_data(color.r * color2.r, 0, 255);
	mult.g = check_data(color.g * color2.g, 0, 255);
	mult.b = check_data(color.b * color2.b, 0, 255);
	return (mult);
}

t_vec3	vec3_ambiant(t_rgb col, t_rgb color, float light_ratio)
{
	t_vec3	ambiant;

	ambiant.x = check_data(col.r * (color.r / 255) * light_ratio, 0, 255);
	ambiant.y = check_data(col.g * (color.g / 255) * light_ratio, 0, 255);
	ambiant.z = check_data(col.b * (color.b / 255) * light_ratio, 0, 255);
	return (ambiant);
}

t_rgb	vec3_ambiant2(t_rgb col, t_rgb color, float light_ratio)
{
	t_rgb	ambiant;

	ambiant.r = check_data(col.r * color.r * light_ratio, 0, 255);
	ambiant.g = check_data(col.g * color.g * light_ratio, 0, 255);
	ambiant.b = check_data(col.b * color.b * light_ratio, 0, 255);
	return (ambiant);
}

t_rgb	mult_rgb(t_rgb ambiant, double intensity)
{
	t_rgb	new;

	new.r = check_data(ambiant.r * intensity, 0, 255);
	new.g = check_data(ambiant.g * intensity, 0, 255);
	new.b = check_data(ambiant.b * intensity, 0, 255);
	return (new);
}

t_rgb	add_rgb(t_rgb a, t_rgb b)
{
	t_rgb	added;

	added.r = check_data(a.r + b.r, 0, 255);
	added.g = check_data(a.g + b.g, 0, 255);
	added.b = check_data(a.b + b.b, 0, 255);
	return (added);
}

t_rgb	vect_to_rgb(t_vec3 vec)
{
	t_rgb	color;

	color.r = (int)vec.x;
	color.g = (int)vec.y;
	color.b = (int)vec.z;
	return (color);
}
