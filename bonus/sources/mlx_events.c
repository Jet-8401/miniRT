/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 01:45:02 by akinzeli          #+#    #+#             */
/*   Updated: 2024/09/11 16:24:56 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minirt.h"

#define MOVING_RATIO 1.2f

int	close_window(t_threads_container *container)
{
	uint16_t	t;

	t = 0;
	container->do_exit = true;
	while (t < container->threads_number)
		pthread_join(container->threads[t].thread_id, NULL);
	ft_destroy_display(container->scene);
	gc_dump(NULL);
	exit(0);
	return (0);
}

static void check_movements(int keycode, int method, t_vec3 *movs)
{
	double		*axis;
	bool		neg_value;

	axis = NULL;
	neg_value = false;
	if (keycode == 'z' || keycode == 's')
		axis = &movs->z;
	else if (keycode == 'q' || keycode == 'd')
		axis = &movs->x;
	else if (keycode == ' ' || keycode == 'c')
		axis = &movs->y;
	if (!axis)
		return ;
	if (method == KeyRelease)
	{
		*axis = 0;
		return ;
	}
	if (keycode == 's' || keycode == 'q' || keycode == 'c')
		neg_value = true;
	*axis = (MOVING_RATIO * ((neg_value * -2) + 1));
}

int	key_press(int keycode, t_threads_container *container)
{
	printf("keycode=%d\n", keycode);
	check_movements(keycode, KeyPress, &container->scene->cam->movements);
	if (keycode == XK_Escape)
		close_window(container);
	return (0);
}

int	key_release(int keycode, t_threads_container *container)
{
	check_movements(keycode, KeyRelease, &container->scene->cam->movements);
	return (0);
}
