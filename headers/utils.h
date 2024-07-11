/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:59:32 by jullopez          #+#    #+#             */
/*   Updated: 2024/07/11 17:07:07 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef unsigned char	t_u8b;

typedef struct s_vec3
{
	double				x;
	double				y;
	double				z;
}						t_vec3;

typedef struct s_rgb
{
	t_u8b				r;
	t_u8b				g;
	t_u8b				b;
}						t_rgb;

typedef struct s_sphere
{
	t_vec3				pos;
	float				diameter;
	t_rgb				color;
	struct s_sphere		*next;
}						t_sphere;

typedef struct s_plane
{
	t_vec3				pos;
	t_vec3				dir;
	float				diameter;
	float				height;
	t_rgb				color;
	struct s_plane		*next;
}						t_plane;

typedef struct s_cylinder
{
	t_vec3				pos;
	t_vec3				dir;
	float				diameter;
	float				height;
	t_rgb				color;
	struct s_cylinder	*next;
}						t_cylinder;

// brightness is a ratio between 0 and 1
typedef struct s_light
{
	t_vec2				pos;
	float				brightness;
}						t_light;

typedef struct s_lst
{
	void			*content;
	struct s_lst	*next;
	struct s_lst	*prev;
}	t_lst;

#endif
