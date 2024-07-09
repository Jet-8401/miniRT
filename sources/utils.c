/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jullopez <jullopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:27:54 by jullopez          #+#    #+#             */
/*   Updated: 2024/07/09 16:53:22 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_err(const char *line, char perror_invoc)
{
	write(2, PROG_NAME, ft_strlen(PROG_NAME));
	if (perror_invoc)
	{
		perror(line);
		return ;
	}
	write(2, line, ft_strlen(line));
	write(2, "\n", 1);
}

int	end_with(const char *haystack, const char *needle)
{
	long	i;
	long	base;

	if (!haystack || !needle)
		return (0);
	i = ft_strlen(needle);
	base = ft_strlen(haystack) - i++;
	if (base < 0)
		return (0);
	while (--i > 0)
		if (haystack[base + i] != needle[i])
			return (0);
	return (1);
}
