/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:17:20 by jullopez          #+#    #+#             */
/*   Updated: 2024/09/18 19:53:48 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

void	ft_err(const char *line, char perror_invoc)
{
	if (write(2, PROG_NAME, ft_strlen(PROG_NAME)) == -1
		|| write(2, "Error\n", 6) == -1)
		return ;
	if (perror_invoc)
	{
		perror(line);
		return ;
	}
	if (write(2, line, ft_strlen(line)) == -1 || write(2, "\n", 1) == -1)
		return ;
}

/* Note on 'parser_err_line' & 'parser_err_col':
 * Thoses function act as getter_setter for 'parser_error' fuction.
 * If -1 is given as a parameter the function just return the value,
 * else if the number if higher it set it as the new value and return it.
 */
int	parser_err_line(int n)
{
	static int	line;

	if (n == -1)
		return (line);
	return (line = n);
}

void	parser_error(const char *message)
{
	const char	*error;
	char		*convs;

	convs = ft_itoa(parser_err_line(-1));
	error = strs_join((const char *[]){"line: ", convs, " ", message, NULL});
	ft_err(error, 0);
	gc_dump(&convs[0]);
}
