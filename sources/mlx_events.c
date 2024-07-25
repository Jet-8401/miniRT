/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jullopez <jullopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:26:08 by jullopez          #+#    #+#             */
/*   Updated: 2024/07/23 16:26:09 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

int	close_window(t_display *display)
{
	if (display)
		ft_destroy_display(display);
	gc_dump(NULL);
	exit(0);
	return (0);
}

int	key_handler(int keycode, t_scene *scene)
{
	//printf("keycode=%d\n", keycode);
	if (keycode == 65451)
		scene->cam->pos.z += 1;
	else if (keycode == 65453)
		scene->cam->pos.z -= 1;
	else if (keycode == 65361)
		scene->cam->pos.x += 0.1f;
	else if (keycode == 65363)
		scene->cam->pos.x -= 0.1f;
	else if (keycode == 65362)
		scene->cam->pos.y -= 0.1f;
	else if (keycode == 65364)
		scene->cam->pos.y += 0.1f;
	if (keycode == XK_Escape)
		close_window(&scene->display);
	return (0);
}
