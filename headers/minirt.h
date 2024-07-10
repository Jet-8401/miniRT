/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jullopez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:37:50 by jullopez          #+#    #+#             */
/*   Updated: 2024/07/09 17:30:49 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libs/mlx/mlx.h"
# include "../libs/libft-gc/libft-gc.h"
# include "utils.h"
# include <math.h>
# include <stdio.h> // for perror !
# include <fcntl.h>

# define PROG_NAME "minirt: "
# define READ_BUF_SIZE 1024

# define ERR_FILE_EXT "not a .rt extension"

/* Notes:
 * light ration is between 0 and 1
 * plane, sphere, cylinder are arrays of structs
 * that are null terminated and not a linked list
 */
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
	t_light		light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
}	t_scene;

/******************************************************************************\
 *                          function declarations                             *
\******************************************************************************/

// parsing.c
void	ft_err(const char *line, char perror_invoc);
int		ft_parsing(t_scene *scene, const char *file_scene);

// utils.c
int		end_with(const char *haystack, const char *needle);

#endif
