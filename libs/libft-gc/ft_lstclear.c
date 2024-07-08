/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Julien Lopez <marvin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:03:24 by Julien Lopez      #+#    #+#             */
/*   Updated: 2024/02/26 09:35:43 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft-gc.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*copy;

	if (!lst || !del)
		return ;
	current = *lst;
	while (current)
	{
		del(current->content);
		copy = current->next;
		free(current);
		current = copy;
	}
	*lst = NULL;
}
