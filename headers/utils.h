/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:59:32 by jullopez          #+#    #+#             */
/*   Updated: 2024/08/21 13:32:04 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdint.h>

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
	t_vec3 pos;
	t_vec3 px;
	t_vec3 py;
	t_vec3 qx;
	t_vec3 qy;
} t_screen;

typedef struct s_fpscounter
{
	t_lst		*snapshots;
	t_u8b		snapshots_samples;
	t_u8b		n_snapshots;
	uint64_t	last_tick;
	uint64_t	total;
}	t_fpscounter;

typedef struct s_object_union
{
	t_sphere sphere;
	t_plane plane;
	t_cylinder cylinder;
} t_object_union;

typedef struct s_obj
{
	t_vec3				pos;
	t_vec3				dir;
	t_object_union 		object;
	float				diameter;
	float				height;
	t_rgb				color;
	char				type;
	struct s_obj		*next;
}				t_obj;


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
	double h;
	t_rgb col;
	t_vec3 hit;
	t_vec3 norm;
	t_vec3 closest_hit;
	t_ray_view shadow_ray;
} t_hit;

typedef struct s_render
{
	t_screen			screen;
	double				a;
	double				b;
	t_ray_view			prime_ray;
	int				color_ambiant;
	t_vec3				pixel_pos;
	t_obj				*obj_closest;
	struct s_hit hit_shadow;
} t_render;




#endif
