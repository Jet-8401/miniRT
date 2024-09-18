/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 01:45:02 by akinzeli          #+#    #+#             */
/*   Updated: 2024/09/11 13:14:00 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

int	close_window(t_scene *display)
{
	ft_destroy_display(display);
	gc_dump(NULL);
	exit(0);
	return (0);
}

int	key_handler(int keycode, t_scene *scene)
{
	if (keycode == XK_Escape)
		close_window(scene);
	return (0);
}
