/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:59:32 by jullopez          #+#    #+#             */
/*   Updated: 2024/09/11 15:37:42 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <pthread.h>
# include <stdint.h>
# include <stdlib.h>

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

enum					e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	DISK,
	TRIANGLE
};

typedef struct s_object
{
	t_vec3				pos;
	t_vec3				dir;
	t_vec3 				v0;
	t_vec3 				v1;
	t_vec3 				v2;
	t_vec3 				a;
	t_vec3 				b;
	t_vec3 				c;
	t_vec3 				edge0;
	t_vec3 				edge1;
	t_vec3 				edge2;
	t_rgb				color;
	float				diameter;
	float				height;
	float				radius;
	enum e_obj_type		type;
	struct s_object		*next;
	struct s_object		*start_cap;
	struct s_object		*end_cap;
}						t_object;

// brightness is a ratio between 0 and 1
typedef struct s_light
{
	t_vec3				pos;
	float				brightness;
	t_rgb				color;
	struct s_light		*next;
}						t_light;

typedef struct s_lst
{
	void				*content;
	struct s_lst		*next;
	struct s_lst		*prev;
}						t_lst;

typedef struct s_screen
{
	size_t				width;
	size_t				height;
	double				aspect_ratio;
	double				scale;
	t_vec3				right;
	t_vec3				up;
}						t_screen;

typedef struct s_fpscounter
{
	t_lst				*snapshots;
	t_u8b				snapshots_samples;
	t_u8b				n_snapshots;
	uint64_t			last_tick;
	uint64_t			total;
}						t_fpscounter;

typedef struct s_image
{
	void				*img;
	uint8_t				*addr;
	int					bpp;
	int					line_len;
	int					big_endian;
}						t_image;

typedef struct s_mlx
{
	void				*mlx;
	void				*win;
	t_image				img;
	t_fpscounter		*fps_counter;
}						t_mlx;

typedef struct s_ray_view
{
	t_vec3				origin;
	t_vec3				direction;
}						t_ray_view;

typedef struct s_hit
{
	double				t;
	double				t2;
	t_vec3				hit;
	t_vec3				norm;
	t_object			*object;
}						t_hit;

typedef struct s_render
{
	t_ray_view			prime_ray;
	int					color_ambiant;
	double				light_distance;
	t_rgb				final_color;
	t_rgb				ambiant_light;
	t_rgb				color;
}						t_render;

typedef struct s_equation
{
	double				a;
	double				b;
	double				c;
	double				delta;
	t_vec3				origin;
	t_vec3				temp;
}						t_equation;

#endif
