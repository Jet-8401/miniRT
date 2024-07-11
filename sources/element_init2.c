/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_init2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:57:10 by akinzeli          #+#    #+#             */
/*   Updated: 2024/07/11 13:45:01 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

int	add_diameter(char *size, float *diameter)
{
	*diameter = (float)ft_atof(size);
	return (0);
}

int	add_height(char *size, float *height)
{
	*height = (float)ft_atof(size);
	return (0);
}

