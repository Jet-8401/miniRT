/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 01:45:02 by akinzeli          #+#    #+#             */
/*   Updated: 2024/09/11 14:27:05 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/bonus_header/minirt.h"

#define MOVING_RATIO 0.5f

int	close_window(t_scene *display)
{
	ft_destroy_display(display);
	gc_dump(NULL);
	exit(0);
	return (0);
}

int	key_handler(int keycode, t_scene *scene)
{
	printf("keycode=%d\n", keycode);
	if (keycode == 65451)
		scene->cam->pos.z += 0.5;
	else if (keycode == 65453)
		scene->cam->pos.z -= 0.5;
	else if (keycode == 65361)
		scene->cam->pos.x -= MOVING_RATIO;
	else if (keycode == 65363)
		scene->cam->pos.x += MOVING_RATIO;
	else if (keycode == 65362)
		scene->cam->pos.y += MOVING_RATIO;
	else if (keycode == 65364)
		scene->cam->pos.y -= MOVING_RATIO;
	else if (keycode == XK_Escape)
		close_window(scene);
	return (0);
}
