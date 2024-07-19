/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:37:50 by jullopez          #+#    #+#             */
/*   Updated: 2024/07/19 15:26:35 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#ifndef M_PI
#   define M_PI 3.1415926535897932384626433832
#endif

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

# define PROG_NAME "minirt: "

# define ERR_FILE_EXT "not a .rt extension"
# define ERR_UNKNOWN_ID "unrecognized identifier"
# define ERR_MULTIPLE_IDENTIFIERS "file contain duplicate identifiers"

# define WIDTH 1280
# define HEIGHT 720
# define EPSILON 0.0001

typedef struct s_scene
{
	struct s_ambient
	{
		float	light_ratio;
		t_rgb	color;
	}	ambient;
	struct s_cam
	{
		t_vec3	pos;
		t_vec3	dir;
		t_u8b	fov;
	}	cam;
	t_light		*light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	t_mlx		*mlx;
	t_screen	*screen;
	t_obj		*obj;
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
int				set_vector3D(t_vec3 *vec, char *coordinate);
int				set_normalized_vector3D(t_vec3 *vec, char *coordinate);

// add_list.c
void			add_sphere(t_scene *scene, t_sphere *object);
void			add_plane(t_scene *scene, t_plane *object);
void			add_cylinder(t_scene *scene, t_cylinder *object);

// mlx_init.c

int				init_mlx_all(t_scene *scene);
int				init_mlx_window(t_mlx *mlx);
void			destroy_mlx(t_mlx *mlx);
void init_objects(t_scene *scene);

// render.c

void init_camera(t_scene *scene);
void render_scene(t_scene *scene);
void pixel_draw(t_scene *scene, t_render render);
int new_rgb(int r, int g, int b);
void new_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
t_vec3 ambiant_color(t_ray_view *ray, t_scene *scene);
t_hit intersect(t_ray_view *ray, t_scene *scene);
t_vec3 new_color(t_scene *scene, t_hit hit, t_vec3 light_dir);
t_vec3 share_light(t_hit hit, t_light *light, double h);
t_vec3 add_color(t_vec3 a, t_vec3 b);
int new_shader(t_scene *scene, t_hit hit, t_light *light);
double final_shadow(t_vec3 in);
void init_ret(t_vec3 *ret);
int in_scene(t_vec3 ray, t_vec3 norm);
t_hit intersect_sphere(t_ray_view *ray, t_sphere *sphere, t_hit hit);
t_hit intersect_plane(t_ray_view *ray, t_plane *plane, t_hit hit);
t_hit intersect_cylinder(t_ray_view *ray, t_cylinder *cylinder, t_hit hit);
double cylinder_inside(t_ray_view *ray, t_cylinder *cylinder);
double plane_inside(t_ray_view *ray, t_plane *plane);
double sphere_inside(t_ray_view *ray, t_sphere *sphere);
t_vec3 vec3_ambiant(t_rgb col, t_rgb color, float light_ratio);
t_vec3 add_vec3(t_vec3 a, t_vec3 b);
t_vec3 mult_color_vec3(t_rgb color, double b);
t_vec3 mult_vec3(t_vec3 a, double b);
t_vec3 sub_vec3(t_vec3 a, t_vec3 b);
double dot(t_vec3 a, t_vec3 b);
t_ray_view new_ray(t_scene *scene, t_render render);
t_vec3 new_normalized(t_vec3 new);
void normalize(t_vec3 *new);
t_vec3 merge_vect(t_vec3 a, t_vec3 b);
double pick_inter_cylinder(double a, double b, double delta, t_ray_view *ray, t_vec3 n, t_vec3 oc, t_cylinder *cylinder);

// ft_atof.c
double			ft_atof(char *str);
void			ft_atof_bis(char *str, long double *res, int *neg);

#endif

