/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jullopez <jullopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:54:35 by jullopez          #+#    #+#             */
/*   Updated: 2024/09/13 18:54:35 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minirt.h"

static void	thread_render(t_render_thread *thread)
{
	sem_wait(&thread->container->image_rendering);
	pthread_mutex_lock(&thread->render_lock);
	usleep(500);
	pthread_mutex_unlock(&thread->render_lock);
}

void	*thread_routine(void *arg)
{
	t_render_thread	*thread;

	thread = arg;
	sem_post(&thread->container->threads_routines);
	while (1) // to change
		thread_render(thread);
	exit(0);
	return (NULL);
}
