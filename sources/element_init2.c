/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_init2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:57:10 by akinzeli          #+#    #+#             */
/*   Updated: 2024/07/12 13:14:32 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

int	set_diameter(char *size, float *diameter)
{
	if (check_HD(size) == -1)
		return (-1);
	*diameter = (float)ft_atof(size);
	return (0);
}

int	set_height(char *size, float *height)
{
	if (check_HD(size) == -1)
		return (-1);
	*height = (float)ft_atof(size);
	return (0);
}
