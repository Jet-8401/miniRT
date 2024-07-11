/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:37:50 by jullopez          #+#    #+#             */
/*   Updated: 2024/07/11 13:40:32 by jullopez         ###   ########.fr       */
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
		int		flag;
		t_rgb	color;
	} * ambient;
	struct		s_cam
	{
		t_vec3	pos;
		t_vec3	dir;
		t_u8b	fov;
		int		flag;
	} * cam;
	t_light		*light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
}				t_scene;

/******************************************************************************\
 *                          function declarations                             *
\******************************************************************************/

// parsing.c
int		ft_parsing(t_scene *scene, const char *file_scene);

// utils.c
int		ft_isspace(char c);
void	ft_err(const char *line, char perror_invoc);
void	parser_error(long coords[2], const char *message);
int		end_with(const char *haystack, const char *needle);
int		ft_strlen2(char **argv);

// props_init.c
int				ambient_init(t_scene *scene, char **args);
int				camera_init(t_scene *scene, char **args);
int				light_init(t_scene *scene, char **args);

// forms_init.c
int				sphere_init(t_scene *scene, char **args);
int				plane_init(t_scene *scene, char **args);
int				cylinder_init(t_scene *scene, char **args);

// struct_init.c

int				add_camera_value(t_scene *scene, char **args);
int				add_ambiant_value(t_scene *scene, char **args);
int				add_light_value(t_scene *scene, char **args);
int				add_sphere_value(t_scene *scene, char **args);
int				add_plane_value(t_scene *scene, char **args);

// struct_init2.c

int				add_cylinder_value(t_scene *scene, char **args);

// element_init.c

int				add_fov(char *fov, int *new_fov);
int				add_3dvector(char *vector, t_vec3 *dir);
int				add_coordinate(char *coor, t_vec3 *loc);
int				add_ratio(char *ratio, float *new_ratio);
int				add_rgb(char *rgb, t_rgb *color);

// element_init2.c

int				add_diameter(char *size, float *diameter);
int				add_height(char *size, float *height);

// parsing_checker.c

int				check_fov(char *fov);
int				check_3d_vector(char *vector);
int				check_3dvector_value(char **vector);
int				check_coordinate(char *coordinate);
int				check_coordinate_value(char **coordinate);

// parsing_checker2.c

int				check_ratio(char *ratio);
int				check_rgb(char *rgb);
int				check_rgb_value(char **color);
int				check_HD(char *hd);

// ft_atof.c

double			ft_atof(char *str);
void			ft_atof_bis(char *str, long double *res, int *neg);

#endif
