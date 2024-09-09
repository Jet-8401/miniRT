/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:18:15 by akinzeli          #+#    #+#             */
/*   Updated: 2024/09/01 23:18:51 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

t_u8b	check_data(int n, int min, int max)
{
	if (n > max)
		return (max);
	else if (n < min)
		return (min);
	return (n);
}
