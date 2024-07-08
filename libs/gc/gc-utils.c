/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc-utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jullopez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:43:25 by jullopez          #+#    #+#             */
/*   Updated: 2024/06/22 02:55:17 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

static unsigned long	ft_strlen(const char *s)
{
	unsigned long	i;

	i = 0;
	while (s[i++])
		;
	return (i - 1);
}

void	gc_error(const char *msg)
{
	if (write(2, GC_ERR, ft_strlen(GC_ERR))
		&& write(2, msg, ft_strlen(msg)))
		return ;
}
