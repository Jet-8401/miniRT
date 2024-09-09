/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:16:38 by jullopez          #+#    #+#             */
/*   Updated: 2024/09/01 23:36:31 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

int	main(int argc, char *argv[])
{
	t_scene	scene;

	if (argc != 2)
		return (ft_err(ERR_USAGE, 0), 0);
	if (ft_parsing(&scene, argv[1]) == -1)
		return (gc_dump(NULL), 0);
	if (init_mlx_all(&scene) == -1)
		return (gc_dump(NULL), 0);
	mlx_hook(scene.mlx.win, 17, 0, close_window, &scene);
	mlx_hook(scene.mlx.win, KeyPress, KeyPressMask, key_handler, &scene);
	mlx_loop_hook(scene.mlx.mlx, &render_scene, &scene);
	mlx_loop(scene.mlx.mlx);
	//gc_dump(NULL);
	return (0);
}
