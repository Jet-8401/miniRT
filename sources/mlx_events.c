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

#define MOVING_RATIO 0.5f

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
	printf("keycode=%d\n", keycode);

	switch (keycode)
	{
		case 65451:
			scene->cam->pos.z += 0.5;
			break ;
		case 65453:
			scene->cam->pos.z -= 0.5;
			break ;
		case 65361:
			scene->cam->pos.x += MOVING_RATIO;
			break ;
		case 65363:
			scene->cam->pos.x -= MOVING_RATIO;
			break ;
		case 65362:
			scene->cam->pos.y -= MOVING_RATIO;
			break ;
		case 65364:
			scene->cam->pos.y += MOVING_RATIO;
			break ;
		case XK_Escape:
			close_window(&scene->display);
			break ;
	}
	return (0);
}
