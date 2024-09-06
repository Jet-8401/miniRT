/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:59:32 by jullopez          #+#    #+#             */
/*   Updated: 2024/09/03 20:05:24 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

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

enum obj_type {
	SPHERE,
	PLANE,
	CYLINDER
};

typedef struct s_object
{
	t_vec3			pos;
	t_vec3			dir;
	t_rgb			color;
	float			diameter;
	float			height;
	float			radius;
	enum obj_type	type;
	struct s_object	*next;
	int				id;
}	t_object;

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

typedef struct s_screen
{
	size_t screen_width;
	size_t screen_height;
	double aspect_ratio;
	double scalar_fov;
	double scale;
	double width;
	t_vec3 right;
	t_vec3 up;
} t_screen;

typedef struct s_fpscounter
{
	t_lst		*snapshots;
	t_u8b		snapshots_samples;
	t_u8b		n_snapshots;
	uint64_t	last_tick;
	uint64_t	total;
}	t_fpscounter;

/*   mlx lib  */

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
	t_fpscounter *fps_counter;
}						t_mlx;


typedef struct s_ray_view
{
	t_vec3				origin;
	t_vec3				direction;
} t_ray_view;

typedef struct s_hit
{
	double		t;
	double		t2;
	t_vec3		hit;
	t_vec3		norm;
	t_object	*object;
}	t_hit;

typedef struct s_render
{
	//t_screen			screen;
	t_ray_view			prime_ray;
	int					color_ambiant;
	double				light_distance;
} t_render;






#endif
