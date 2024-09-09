/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:59:10 by akinzeli          #+#    #+#             */
/*   Updated: 2024/09/09 18:00:49 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

double	ft_atof(char *str)
{
	long double	res;
	int			neg;

	res = 0;
	neg = 0;
	ft_atof_bis(str, &res, &neg);
	if (res > DBL_MAX)
		ft_err("Number bigger than double", 0);
	return (neg ? -res : res);
}

void	ft_atof_bis(char *str, long double *res, int *neg)
{
	int		dote;
	double	scale;

	dote = 0;
	scale = 1;
	if (*str == '-')
	{
		*neg = 1;
		str++;
	}
	while (*str)
	{
		if (dote)
		{
			scale /= 10;
			*res += (*str - '0') * scale;
		}
		else if (*str == '.')
			dote++;
		else
			*res = *res * 10.0 + (*str - '0');
		str++;
	}
}
