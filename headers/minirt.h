/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:37:50 by jullopez          #+#    #+#             */
/*   Updated: 2024/09/09 18:13:04 by akinzeli         ###   ########.fr       */
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
# include <fcntl.h>
# include <float.h>
# include <stdio.h> // for perror !
# include <stdbool.h>
# include <inttypes.h>
# include <sys/time.h>
# include <X11/X.h>
# include <X11/keysym.h>

# define PROG_NAME "minirt: "

# define ERR_FILE_EXT "not a .rt extension"
# define ERR_UNKNOWN_ID "unrecognized identifier"
# define ERR_MULTIPLE_IDENTIFIERS "file contain duplicate identifiers"
# define ERR_MLX_PTR "cannot connect to X server"
# define ERR_MLX_WINDOW "cannot create mlx window"
# define ERR_RENDER_IMG "an error ocured while creating mlx image"
# define ERR_COUNTER_INIT "impossible to init fps counter"

# define WIDTH 1920
# define HEIGHT 1080
# define EPSILON 1e-6
# define WHITE 2147483647
# define FPS_SNAPSHOT_SAMPLES 50

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
	t_object	*object;
	t_mlx		mlx;
	t_screen	screen;
	t_render	render;
}	t_scene;

/******************************************************************************\
 *                          function declarations                             *
\******************************************************************************/

// parsing.c
int	parser_check_capitals(const char *line);
int (*check_identifiers(const char *line))(t_scene *n, char **split);
int	ft_parse_line(t_scene *scene, const char *line);
int				ft_parsing(t_scene *scene, const char *file_scene);
int ft_check_scene(t_scene *scene);

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

// props_init.c
int				ambient_init(t_scene *scene, char **args);
int				camera_init(t_scene *scene, char **args);
int				light_init(t_scene *scene, char **args);

// forms_init.c
int				sphere_init(t_scene *scene, char **args);
int				plane_init(t_scene *scene, char **args);
int				cylinder_init(t_scene *scene, char **args);

// element_init.c
int				set_ratio(char *ratio, float *new_ratio);
int				set_rgb(char *rgb, t_rgb *color);
int				set_float_value(char *size, float *value);
int				set_fov(char *fov, t_u8b *new_fov);

// element_init2.c
int				set_vector3d(t_vec3 *vec, char *coordinate);
int				set_normalized_vector3d(t_vec3 *vec, char *coordinate);

// add_list.c
void			add_object(t_scene *scene, t_object *object);

// mlx_init.c
int				init_mlx_all(t_scene *scene);
int				init_mlx_window(t_mlx *mlx);
void			destroy_mlx(t_mlx *mlx);
void	ft_destroy_display(t_scene *display);
void new_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);


// render.c
void init_camera(t_scene *scene);
int render_scene(t_scene *scene);
void pixel_draw(t_scene *scene, t_render *render);
void new_init_camera(t_scene *scene, t_ray_view *prime_ray, float x, float y);


// 3Dvect.c
t_vec3 merge_vect(t_vec3 a, t_vec3 b);
t_vec3 *normalize_bis(t_vec3 *_new);
t_vec3 normalize(t_vec3 _new);
t_vec3 new_normalized(t_vec3 _new);
double dot(t_vec3 a, t_vec3 b);

// 3Dvect2.c
t_vec3 sub_vec3(t_vec3 a, t_vec3 b);
t_vec3 mult_vec3(t_vec3 a, double b);
t_vec3 add_vec3(t_vec3 a, t_vec3 b);
t_vec3 new_vector(double x, double y, double z);
double vec3_length(t_vec3 vec);


// vec3D_util.c
void	vec3_subtract(t_vec3 *a, t_vec3 *b, t_vec3 *result);
void	vec3_add(t_vec3 *a, t_vec3 *b, t_vec3 *result);
void	vec3_scale(t_vec3 *a, double scalar);
void	vec3_cross(t_vec3 *a, t_vec3 *b, t_vec3 *result);
void	vec3_normalize(t_vec3 *vec);
double	vec3_dot(t_vec3 *a, t_vec3 *b);

// color_vect.c
t_rgb mult_color_vec4(t_rgb color, t_rgb color2);
t_vec3 vec3_ambiant(t_rgb col, t_rgb color, float light_ratio);
t_rgb mult_rgb(t_rgb ambiant, double intensity);
t_rgb add_rgb(t_rgb a, t_rgb b);
t_rgb vect_to_rgb(t_vec3 vec);

// form_intersect.c
bool	intersect_sphere(t_ray_view *ray, t_object *sphere, t_hit *hit);
bool	intersect_plane(t_ray_view *ray, t_object *plane, t_hit *hit);
bool	intersect_cylinder(t_ray_view *ray, t_object *cylinder, t_hit *hit);
bool	intersect_disk(t_ray_view *ray, t_object *disk, t_hit *hit);

// fps_counter.c
int			fps_counter_init(t_fpscounter *counter, t_u8b samples);
uint64_t	get_time();
float		fps_count(t_fpscounter *counter);
void		render_time_display(t_mlx *display);
void		fps_display(t_mlx *display);

// intersect.c
bool	intersect(t_render *render, t_object *obj, t_hit *hit);
bool	intersect_shadow(t_render *render, t_scene *scene, t_hit *hit);
bool	does_intersect(t_render *render, t_object *obj, t_hit *hit);


// light.c
t_rgb ambiant_color(t_render *render, t_scene *scene);
t_rgb light_handler(t_scene *scene, t_render *render, t_hit *hit);
bool new_shadow_ray(t_scene *scene, t_hit *hit, t_render *render);

// mlx_events.c
int	close_window(t_scene *display);
int	key_handler(int keycode, t_scene *scene);

// utils2.c
int color_rgb(t_rgb color);
t_u8b check_data(int n, int min, int max);


// ft_atof.c
double			ft_atof(char *str);
void			ft_atof_bis(char *str, long double *res, int *neg);



// TEST

bool	intersect_cylinder_math(t_ray_view *ray, t_object *cylinder, t_hit *hit);
void	check_cylinder_data(t_ray_view *ray, t_object *cylinder, double *t);
bool	calculation(double *t, double *t2, t_ray_view *ray, t_object *cylinder);



#endif
