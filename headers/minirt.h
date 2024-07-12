/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:37:50 by jullopez          #+#    #+#             */
/*   Updated: 2024/07/12 14:14:55 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libs/libft-gc/libft-gc.h"
# include "../libs/mlx/mlx.h"
# include "utils.h"
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <stdio.h> // for perror !

# define PROG_NAME "minirt: "
# define READ_BUF_SIZE 1024

# define ERR_FILE_EXT "not a .rt extension"
# define ERR_UNKNOWN_ID "unrecognized identifiers"

typedef struct s_scene
{
	struct		s_ambient
	{
		float	light_ratio;
		t_rgb	color;
	} ambient;
	struct		s_cam
	{
		t_vec3	pos;
		t_vec3	dir;
		t_u8b	fov;
	} cam;
	t_light		*light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
}				t_scene;

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
void			parser_error(long l, long c, const char *message);

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
int				set_diameter(char *size, float *diameter);
int				set_height(char *size, float *height);
int				set_fov(char *fov, t_u8b *new_fov);

// element_init2.c

int				set_vector3D(t_vec3 *vec, char *coordinate);
int				set_normalized_vector3D(t_vec3 *vec, char *coordinate);

// parsing_checker.c

int				check_coordinate_value(char **coordinate);
int				check_ratio(char *ratio);
int				check_rgb(char *rgb);
int				check_rgb_value(char **color);
int				check_HD(char *hd);


// add_list.c

void			add_sphere(t_scene *scene, t_sphere *new);
void			add_plane(t_scene *scene, t_plane *new);
void			add_cylinder(t_scene *scene, t_cylinder *new);

// ft_atof.c
double			ft_atof(char *str);
void			ft_atof_bis(char *str, long double *res, int *neg);

#endif
