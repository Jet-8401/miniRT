/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:27:54 by jullopez          #+#    #+#             */
/*   Updated: 2024/07/11 13:40:15 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

int	ft_isspace(char c)
{
	return (c == '\t' || c == ' ');
}

char	*strs_join(const char **strs)
{
}

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

void	parser_error(long coords[2], const char *message)
{
	static char	*predefined[2] = {" col: ", "(line: "};
	char	*msg;
	char		*itoa;
	const char	*oldmsg;
	int			i;

	strs_join((const char *[3]){message, predefined[0], predefined[1]});
	i = -1;
	oldmsg = message;
	message = ft_strjoin(") ", message);
	gc_free((void *) oldmsg);
	while (++i < 2)
	{
		itoa = ft_itoa(coords[i]);
		msg = ft_strjoin(predefined[i], itoa);
		oldmsg = message;
		message = ft_strjoin(msg, message);
		gc_free((void *) oldmsg);
		gc_free(itoa);
		gc_free(msg);
	}
	ft_err(message, 0);
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

int	ft_strlen2(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
		i++;
	return (i - 1);
}
