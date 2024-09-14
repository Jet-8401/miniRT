/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:36:17 by akinzeli          #+#    #+#             */
/*   Updated: 2024/09/11 16:24:56 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minirt.h"

int	check_value(char *number, bool have_floating_point)
{
	int		c;
	bool	floating_point;

	c = (number[0] == '-' || number[0] == '+') - 1;
	floating_point = 0;
	while (number[++c])
	{
		if (number[c] == '.')
		{
			if (floating_point || !have_floating_point)
				return (-1);
			floating_point = 1;
			continue ;
		}
		if (number[c] < '0' || number[c] > '9')
			return (-1);
	}
	return (0);
}

int	check_numbers_value(char **numbers, bool have_floating_point)
{
	int	i;

	i = -1;
	while (numbers[++i])
		if (check_value(numbers[i], have_floating_point) == -1)
			return (-1);
	return (0);
}
