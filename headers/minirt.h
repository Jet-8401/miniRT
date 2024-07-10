/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:37:50 by jullopez          #+#    #+#             */
/*   Updated: 2024/07/10 18:01:02 by akinzeli         ###   ########.fr       */
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

typedef struct s_scene
{
	struct		s_ambient
	{
		float	light_ratio;
		t_rgb	color;
	} * ambient;
	struct		s_cam
	{
		t_vec3	pos;
		t_vec3	dir;
		t_u8b	fov;
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
void			ft_err(const char *line, char perror_invoc);
int				ft_parsing(t_scene *scene, const char *file_scene);

// utils.c
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

// ft_atof.c

double			ft_atof(char *str);
void			ft_atof_bis(char *str, long double *res, int *neg);

#endif
