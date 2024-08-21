/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jullopez <jullopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 02:47:36 by jullopez          #+#    #+#             */
/*   Updated: 2024/07/21 02:47:37 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

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

// get time in microseconds
uint64_t	get_time()
{
	static struct timeval	tv;
	static uint64_t			timestamp;

	gettimeofday(&tv, NULL);
	// change multiplication by bitshifting
	timestamp = tv.tv_sec * 1e6 + tv.tv_usec;
	return (timestamp);
}

// get the time between the last frame and the current tick
// add that to the average
// return the average divided by the number of snapshots
float	fps_count(t_fpscounter *counter)
{
	static float	result;
	static uint64_t	delta;
	static uint64_t	now;

	// if there now last_tick, set it and skip
	if (!counter->last_tick)
		return (counter->last_tick = get_time(), 0);
	now = get_time();
	// calculate the delta from the difference
	// of the last_tick and the new tick
	//printf("last_tick=%ld\n", counter->last_tick);
	//printf("now      =%ld\n", now);
	delta = now - counter->last_tick;
	//printf("delta=%ld\n", delta);
	*(uint64_t *) counter->snapshots->content = delta;
	// skip for the next snapshot
	counter->snapshots = counter->snapshots->next;
	counter->last_tick = now;
	counter->total += delta;
	//printf("total=%ld\n", counter->total);
	//printf("snapshots=%d\n", counter->current_snapshots);
	// check if the number of snapshots is the same as asked.
	// if not, it return to prevent from substracting the lastest delta
	if (counter->n_snapshots < counter->snapshots_samples)
		return (counter->n_snapshots++,
			1e6 / ((float) counter->total / counter->n_snapshots));
	result = (float) counter->total / counter->n_snapshots;
	counter->total -= *((uint64_t *) counter->snapshots->prev->content);
	return (1e6 / result);
}

void	fps_display(t_display *display)
{
	static char	*string;

	string = ft_itoa(fps_count(display->fps_counter));
	mlx_string_put(display->mlx_ptr, display->window, 0, 10, STRING_COLOR,
		string);
	gc_free(string);
	string = NULL;
}
