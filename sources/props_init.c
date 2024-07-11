/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   props_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:55:57 by jullopez          #+#    #+#             */
/*   Updated: 2024/07/11 13:11:25 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

int	ambient_init(t_scene *scene, char **args)
{
	if (scene->ambient->flag != 0)
		return (ft_err("Ambiant light already exist", 0), -1);
	if (ft_strlen2(args) != 3)
		return (ft_err("Bad arguments number ambiant", 0), -1);
	if (check_ratio(args[1]) == -1)
		return (ft_err("Bad ratio number ambiant", 0), -1);
	if (check_rgb(args[2]) == -1)
		return (ft_err("Bad RGB arguments ambiant", 0), -1);
	if (add_ambiant_value(scene, args) == -1)
		return (ft_err("Wrong ambiant values", 0), -1);
	return (0);
}

int	camera_init(t_scene *scene, char **args)
{
	if (scene->cam->flag != 0)
		return (ft_err("Camera already exist", 0), -1);
	if (ft_strlen2(args) != 4)
		return (ft_err("Bad arguments number camera", 0), -1);
	if (check_coordinate(args[1]) == -1)
		return (ft_err("Bad coordinate for camera", 0), -1);
	if (check_3d_vector(args[2]) == -1)
		return (ft_err("Bad arguments 3D vector camera", 0), -1);
	if (check_fov(args[3]) == -1)
		return (ft_err("Bad fov for camera", 0), -1);
	if (add_camera_value(scene, args) == -1)
		return (ft_err("Wrong camera values", 0), -1);
	return (0);
}

int	light_init(t_scene *scene, char **args)
{
	if (scene->light->flag != 0)
		return (ft_err("light already exist", 0), -1);
	if (ft_strlen2(args) != 3)
		return (ft_err("Bad arguments number light", 0), -1);
	if (check_coordinate(args[1]) == -1)
		return (ft_err("Bad coordinate light", 0), -1);
	if (check_ratio(args[2]) == -1)
		return (ft_err("Bad light ratio", 0), -1);
	if (add_light_value(scene, args) == -1)
		return (ft_err("Wrong light values", 0), -1);
	return (0);
}
