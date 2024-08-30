/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:37:50 by jullopez          #+#    #+#             */
/*   Updated: 2024/07/15 23:28:11 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# ifndef M_PI
#  define M_PI 3.1415926535897932384626433832
# endif

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libs/libft-gc/libft-gc.h"
# include "../libs/mlx/mlx.h"
# include "utils.h"
# include <stdint.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <float.h> // don't work for norminette
# include <stdio.h> // for perror
# include <sys/time.h>
# include <X11/X.h>
# include <X11/keysym.h>

// for debug
#define STRING_COLOR 0xFFFFFF

# define PROG_NAME "minirt: "
# define FPS_SNAPSHOT_SAMPLES 50

# define WIDTH 1920
# define HEIGHT 1080
# define EPSILON 1e-6
# define WHITE 2147483647

# define ERR_FILE_EXT "not a .rt extension"
# define ERR_UNKNOWN_ID "unrecognized identifier"
# define ERR_MULTIPLE_IDENTIFIERS "file contain duplicate identifiers"
# define ERR_MLX_PTR "cannot connect to X server"
# define ERR_MLX_WINDOW "cannot create mlx window"
# define ERR_RENDER_IMG "an error ocured while creating mlx image"
# define ERR_COUNTER_INIT "impossible to init fps counter"

/* bpp = bits_per_pixel
 * lsize = line_size
 */
typedef struct s_display
{
	void			*mlx_ptr;
	void			*window;
	void			*render_img;
	uint32_t		*data;
	t_fpscounter	*fps_counter;
	int				height;
	int				width;
	double			aspect_ratio;
	int				bpp;
	int				lsize;
	int				big_endian;
}	t_display;

typedef struct s_screen
{
	uint64_t	screen_width;
	uint64_t	screen_height;
	double		aspect_ratio;
	double		scalar_fov;
	double		scale;
	double		width;
	t_vec3		right;
	t_vec3		up;
} t_screen;

typedef struct s_scene
{
	struct s_ambient
	{
		float	light_ratio;
		t_rgb	color;
	}	*ambient;
	struct s_cam
	{
		t_vec3	pos;
		t_vec3	dir;
		t_u8b	fov;
	}	*cam;
	t_light		*light;
	t_object	*objects;
	t_display	display;
}	t_scene;

/******************************************************************************\
 *                          function declarations                             *
\******************************************************************************/

// main.c
void			print_all(t_scene *scene);
void			print_form_list(t_scene *scene);
void			print_sphere_list(t_scene *scene);
void			print_plane_list(t_scene *scene);
void			print_cylinder_list(t_scene *scene);

// parsing.c
int				ft_parsing(t_scene *scene, const char *file_scene);

// error.c
void			ft_err(const char *line, char perror_invoc);
int				parser_err_line(int n);
int				parser_err_col(int n);
void			parser_error(const char *message);

// list_utils.c
t_lst			*lst_trunc(t_lst **origin);
t_lst			*lst_new(void *content);
t_lst			*lst_append(t_lst **origin, t_lst *list);

// utils.c
int				ft_isspace(char c);
char			*strs_join(const char **strs);
void			free_double_array(char **split);
int				end_with(const char *haystack, const char *needle);
int				ft_strlen2(char **argv);

// parsing_checker.c
int				check_value(char *number, bool have_floating_point);
int				check_numbers_value(char **numbers, bool have_floating_point);
int				ft_check_scene(t_scene *scene);

void			init_pointer_objects(t_scene *scene);

// props_init.c
int				ambient_init(t_scene *scene, char **args);
int				camera_init(t_scene *scene, char **args);
int				light_init(t_scene *scene, char **args);

// forms_init.c
int				sphere_init(t_scene *scene, char **args);
int				plane_init(t_scene *scene, char **args);
int				cylinder_init(t_scene *scene, char **args);

// elements_setter.c
int				set_ratio(char *ratio, float *new_ratio);
int				set_rgb(char *rgb, t_rgb *color);
int				set_float_value(char *size, float *value);
int				set_fov(char *fov, t_u8b *new_fov);

// 3Dvector.c
int				set_vector3D(t_vec3 *vec, char *coordinate);
int				set_normalized_vector3D(t_vec3 *vec, char *coordinate);
void			vec3D_normalize(t_vec3 *vec);
double			vec3D_dot(t_vec3 *a, t_vec3 *b);
void			vec3D_cross(t_vec3 *a, t_vec3 *b, t_vec3 *c);
void			vec3D_subtract(t_vec3 *a, t_vec3 *b, t_vec3 *c);
void			vec3D_add(t_vec3 *a, t_vec3 *b, t_vec3 *c);
void			vec3D_mult(t_vec3 *a, float mult, t_vec3 *c);

// add_list.c
void			add_object(t_scene *scene, t_object *object);


// rgb.c
int				rgb_to_int(t_rgb *rgb, t_u8b is_big_endian);

// mlx_init.c
/*
int				init_mlx_all(t_scene *scene);
int				init_mlx_window(t_mlx *mlx);
void			destroy_mlx(t_mlx *mlx);
void init_objects(t_scene *scene, char type);
void add_sphere_obj(t_sphere *sphere, char type, t_obj **object, int *i);
void add_plane_obj(t_plane *plane, char type, t_obj **object, int *i);
void add_cylinder_obj(t_cylinder *cylinder, char type, t_obj **object, int *i);
void print_all_objects(t_obj *obj);
void init_objects_all(t_scene *scene);

// render.c

void init_camera(t_scene *scene);
void render_scene(t_scene *scene);
void pixel_draw(t_scene *scene, t_render *render);
int color_rgb(t_rgb color);
void new_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
t_rgb ambiant_color(t_render *render, t_scene *scene, int depth);
t_obj *intersect(t_render *render, t_obj *obj, t_hit *hit);
int new_intersect(t_render *render, t_obj *obj, t_hit *hit);
bool intersect_sphere(t_ray_view *ray, t_sphere *sphere, t_hit *hit);
bool intersect_plane(t_ray_view *ray, t_plane *plane, t_hit *hit);
t_vec3 vec3_ambiant(t_rgb col, t_rgb color, float light_ratio);
t_vec3 add_vec3(t_vec3 a, t_vec3 b);
t_vec3 mult_vec3(t_vec3 a, double b);
t_vec3 sub_vec3(t_vec3 a, t_vec3 b);
double dot(t_vec3 a, t_vec3 b);
t_vec3 normalize(t_vec3 new);
t_vec3 *normalize_bis(t_vec3 *new);
t_vec3 merge_vect(t_vec3 a, t_vec3 b);
void new_init_camera(t_scene *scene, t_ray_view *prime_ray, float x, float y);
t_vec3 new_vector(double x, double y, double z);
t_rgb vect_to_rgb(t_vec3 vec);
t_rgb light_handler(t_scene *scene, t_render *render, t_hit *hit);
t_vec3 new_normalized(t_vec3 new);
t_rgb mult_rgb(t_rgb ambiant, double intensity);


bool new_shadow_ray(t_scene *scene, t_hit *hit, t_render *render);
int new_intersect2(t_ray_view *render, t_obj *obj, t_hit *hit);
t_rgb mult_color_vec4(t_rgb color, double b);
t_rgb add_rgb(t_rgb a, t_rgb b);
t_u8b check_data(int n, int min, int max);
bool intersect3(t_ray_view *ray, t_render *render, t_hit *hit, t_scene *scene);
double vec3_length(t_vec3 vec);
*/

// ft_atof.c
double			ft_atof(char *str);
void			ft_atof_bis(char *str, long double *res, int *neg);

// display.c
int				ft_init_display(t_display *display, int size_x, int size_y,
					char *title);
void			ft_destroy_display(t_display *display);

// render_time.c
void			render_time_display(t_display *display);

// fps_couter.c
uint64_t		get_time();
int				fps_counter_init(t_fpscounter *counter, t_u8b samples);
float			fps_count(t_fpscounter *counter);
void			fps_display(t_display *display);

// mlx_events.c
int				close_window(t_display *display);
int				key_handler(int keycode, t_scene *scene);

// render.c
int				render_scene(t_scene *scene);

#endif
