/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Julien Lopez <marvin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:28:36 by Julien Lopez      #+#    #+#             */
/*   Updated: 2024/02/26 09:37:02 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft-gc.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*copy;

	result = NULL;
	while (lst)
	{
		copy = ft_lstnew(f(lst->content));
		if (!copy)
		{
			ft_lstclear(&result, del);
			return (NULL);
		}
		ft_lstadd_back(&result, copy);
		lst = lst->next;
	}
	return (result);
}
