/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 02:47:36 by jullopez          #+#    #+#             */
/*   Updated: 2024/09/11 16:24:56 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minirt.h"

int	fps_counter_init(t_fpscounter *counter, t_u8b samples)
{
	t_u8b	i;
	t_lst	*snapshot;

	i = 0;
	snapshot = NULL;
	counter->snapshots_samples = samples;
	if (counter->snapshots_samples == 0)
		return (-1);
	while (i++ < counter->snapshots_samples)
	{
		snapshot = lst_new(gc_calloc(sizeof(uint64_t)));
		if (!snapshot)
			return (-1);
		lst_append(&counter->snapshots, snapshot);
	}
	snapshot->next = counter->snapshots;
	counter->snapshots->prev = snapshot;
	return (0);
}

uint64_t	get_time(void)
{
	static struct timeval	tv;
	static uint64_t			timestamp;

	gettimeofday(&tv, NULL);
	timestamp = tv.tv_sec * 1e6 + tv.tv_usec;
	return (timestamp);
}

/* Each time this function is called it take a snapshot
 * of the timestamp.
 * While n_snapshots < snapshots_samples we accumulate the snapshots,
 * then when the condition is false we just rotate through the samples for
 * setting the snapshots as its an infinite linked list.
*/
float	fps_count(t_fpscounter *counter)
{
	static float	result;
	static uint64_t	delta;
	static uint64_t	now;

	if (!counter->last_tick)
		return (counter->last_tick = get_time(), 0);
	now = get_time();
	delta = now - counter->last_tick;
	*(uint64_t *) counter->snapshots->content = delta;
	counter->snapshots = counter->snapshots->next;
	counter->last_tick = now;
	counter->total += delta;
	if (counter->n_snapshots < counter->snapshots_samples)
		return (counter->n_snapshots++, 1e6 / ((float)counter->total
				/ counter->n_snapshots));
	result = (float)counter->total / counter->n_snapshots;
	counter->total -= *((uint64_t *)counter->snapshots->prev->content);
	return (1e6 / result);
}

// delete for later
void	render_time_display(t_mlx *display)
{
	static char		*string;
	static uint64_t	previous_snapshot;
	uint64_t		new_snapshot;

	new_snapshot = get_time();
	string = ft_itoa(new_snapshot - previous_snapshot);
	mlx_string_put(display->mlx, display->win, 0, 22, WHITE, string);
	previous_snapshot = new_snapshot;
	gc_free(string);
	return ;
}

void	fps_display(t_mlx *display)
{
	static char	*string;

	string = ft_itoa(fps_count(display->fps_counter));
	mlx_string_put(display->mlx, display->win, 0, 10, WHITE, "FPS: ");
	mlx_string_put(display->mlx, display->win, 30, 10, WHITE, string);
	gc_free(string);
	return ;
}
