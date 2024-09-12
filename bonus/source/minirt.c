/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:16:38 by jullopez          #+#    #+#             */
/*   Updated: 2024/09/11 17:36:40 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minirt.h"

int	main(int argc, char *argv[])
{
	t_scene	scene;

	if (argc != 2)
		return (ft_err(ERR_USAGE, 0), 0);
	if (ft_parsing(&scene, argv[1]) == -1)
		return (gc_dump(NULL), 0);
	print_all_light(scene.light);
	if (init_mlx_all(&scene) == -1)
		return (gc_dump(NULL), 0);
	mlx_hook(scene.mlx.win, 17, 0, close_window, &scene);
	mlx_hook(scene.mlx.win, KeyPress, KeyPressMask, key_handler, &scene);
	mlx_loop_hook(scene.mlx.mlx, &render_scene, &scene);
	mlx_loop(scene.mlx.mlx);
	return (0);
}


void print_all_light(t_light *light)
{
	while (light)
	{
		printf("light pos: %f %f %f\n", light->pos.x, light->pos.y, light->pos.z);
		printf("light brightness: %f\n", light->brightness);
		printf("light color: %d %d %d\n", light->color.r, light->color.g, light->color.b);
		light = light->next;
	}
}
