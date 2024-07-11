/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jullopez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:17:20 by jullopez          #+#    #+#             */
/*   Updated: 2024/07/11 14:50:33 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

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

void	parser_error(long l, long c, const char *message)
{
	const char	*error;
	char		*convs[2];

	convs[0] = ft_itoa(l);
	convs[1] = ft_itoa(c);
	error = strs_join((const char *[]){"line: ", convs[0], " col: ", convs[1],
			 " ", message, NULL});
	ft_err(error, 0);
	gc_dump(&convs[0]);
}
