/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jullopez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:37:14 by jullopez          #+#    #+#             */
/*   Updated: 2024/07/08 12:38:34 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt"

void	ft_err(const char *line, bool perror_invoc)
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
