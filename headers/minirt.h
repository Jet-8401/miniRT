/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:37:50 by jullopez          #+#    #+#             */
/*   Updated: 2024/07/17 14:08:11 by akinzeli         ###   ########.fr       */
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

void			init_camera(t_scene *scene);
void			normalize(t_vec3 *v);
void			render_scene(t_scene *scene);
t_vec3			ray_direction(t_scene *scene);
void			raytrace(t_scene *scene, t_vec3 ray, t_vec3 *r);
int intersect_sphere(t_sphere *sphere, t_vec3 camera_position, t_vec3 ray, t_vec3 *intersection, t_vec3 *normal);
int intersect_plane(t_plane *plane, t_vec3 camera_position, t_vec3 ray, t_vec3 *intersection, t_vec3 *normal);
void draw_pixel(t_scene *scene, t_vec3 r, t_rgb color);
int dot(t_vec3 a, t_vec3 b);
int get_color(t_rgb color);
void mlx_pixel_img_put(t_scene *scene, int x, int y, int color);

// ft_atof.c
double			ft_atof(char *str);
void			ft_atof_bis(char *str, long double *res, int *neg);

#endif

