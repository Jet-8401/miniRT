/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:06:55 by jullopez          #+#    #+#             */
/*   Updated: 2024/09/09 18:00:58 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

t_lst	*lst_trunc(t_lst **origin)
{
	t_lst	*copy;

	if (!origin || !*origin)
		return (NULL);
	copy = *origin;
	*origin = copy->prev;
	copy->next = NULL;
	gc_free(copy);
	return (*origin);
}

t_lst	*lst_new(void *content)
{
	t_lst	*list;

	list = gc_malloc(sizeof(t_lst));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	list->prev = NULL;
	return (list);
}

t_lst	*lst_append(t_lst **origin, t_lst *list)
{
	t_lst	*copy;

	copy = *origin;
	if (!list)
		return (NULL);
	if (!*origin)
		return (*origin = list);
	while (copy->next)
		copy = copy->next;
	copy->next = list;
	list->prev = copy;
	return (list);
}
