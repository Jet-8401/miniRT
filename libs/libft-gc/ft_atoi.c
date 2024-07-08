/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Julien Lopez <marvin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:46:27 by Julien Lopez      #+#    #+#             */
/*   Updated: 2024/02/26 09:32:43 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft-gc.h"

static int	ft_isspace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

int	ft_atoi(const char *nptr)
{
	int	integer;
	int	mult;

	integer = 0;
	mult = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		mult = 44 - *nptr++;
	while (ft_isdigit(*nptr))
		integer = (integer * 10) + (*nptr++ - 48);
	return (integer * mult);
}
