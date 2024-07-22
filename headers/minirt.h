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

// for debug
#define WHITE 2147483647

# define PROG_NAME "minirt: "
# define FPS_SNAPSHOT_SAMPLES 50

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
	int				bpp;
	int				lsize;
	int				big_endian;
}	t_display;

// make camera as a mandatory part
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
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
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

// elements_setter.c
int				set_ratio(char *ratio, float *new_ratio);
int				set_rgb(char *rgb, t_rgb *color);
int				set_float_value(char *size, float *value);
int				set_fov(char *fov, t_u8b *new_fov);

// 3Dvector.c
int				set_vector3D(t_vec3 *vec, char *coordinate);
int				set_normalized_vector3D(t_vec3 *vec, char *coordinate);

// add_list.c
void			add_sphere(t_scene *scene, t_sphere *object);
void			add_plane(t_scene *scene, t_plane *object);
void			add_cylinder(t_scene *scene, t_cylinder *object);

// ft_atof.c
double			ft_atof(char *str);
void			ft_atof_bis(char *str, long double *res, int *neg);

// display.c
int				ft_init_display(t_display *screen, int size_x, int size_y,
					char *title);
void			ft_destroy_display(t_display *screen);

// fps_couter.c
int				fps_counter_init(t_fpscounter *counter, t_u8b samples);
int				fps_count(t_fpscounter *counter);
void			fps_display(t_display *display);

#endif
