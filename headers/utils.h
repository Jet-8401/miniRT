/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:59:32 by jullopez          #+#    #+#             */
/*   Updated: 2024/08/29 22:46:39 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdint.h>

typedef unsigned char	t_u8b;

enum	form {
	SPEHRE,
	PLANE,
	CYLINDER
};

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

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}	t_ray;

typedef struct s_object
{
	t_vec3			pos;
	t_vec3			dir;
	float			radius;
	float			height;
	t_rgb			color;
	enum form		type;
	struct s_object *next;
}	t_object;

typedef struct s_form_hit
{
	t_object	*form;
	t_rgb		*color;
	t_vec3		norm;
	t_vec3		hit;	// hit distance
	float		t;		// scalar
}	t_form_hit;

// brightness is a ratio between 0 and 1
typedef struct s_light
{
	t_vec3				pos;
	float				brightness;
}						t_light;

typedef struct s_lst
{
	void				*content;
	struct s_lst		*next;
	struct s_lst		*prev;
}						t_lst;

typedef struct s_fpscounter
{
	t_lst		*snapshots;
	t_u8b		snapshots_samples;
	t_u8b		n_snapshots;
	uint64_t	last_tick;
	uint64_t	total;
}	t_fpscounter;


typedef struct s_image
{
	void				*img;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
}						t_image;

typedef struct s_mlx
{
	void				*mlx;
	void				*win;
	t_image				img;
	t_fpscounter 		*fps_counter;
}						t_mlx;

#endif
