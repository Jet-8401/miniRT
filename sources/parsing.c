/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jullopez <jullopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:15:48 by jullopez          #+#    #+#             */
/*   Updated: 2024/07/10 00:38:50 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

char	*read_file(const char *file)
{
	int		fd;
	char	buffer[READ_BUF_SIZE];
	long	bytes;
	char	*data;
	char	*old;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_err(file, 1), NULL);
	data = "";
	ft_memset(buffer, 0, READ_BUF_SIZE);
	bytes = read(fd, buffer, READ_BUF_SIZE - 1);
	while (bytes > 0)
	{
		old = data;
		data = ft_strjoin(data, buffer);
		if (!data)
			return (NULL);
		gc_free(old);
		bytes = read(fd, buffer, READ_BUF_SIZE - 1);
	}
	return (data);
}

int	ft_parse_line(t_scene *scene, const char *data, long eol)
{
	static char	*identifiers[6] = {"A", "C", "L", "sp", "pl", "cy"};
	static int	(*functions[6])(t_element) = {ambient_init, camera_init,
		light_init, sphere_init, plane_init, cylinder_init};

	// read string, at the begining it should have a string value
	// (only 1 capital letter per files)
	// delimiters are ['\t' ' ' ','] anything else before eol is considered
	// unexpected/unrecognized token.
	return (0);
}

/* Search for a line by skipping every line_breaks=['\n' '\t' ' '],
 * when something else if found parse from that char to a '\n'
 * and create a parameter for each time there is a word.
 * (a word is defined by a separation of spaces and/or tabs)
 * The structure of the code is a linked list of values
 * for wich there is a maxium number that the parser can handle,
 * `sizeof(double)` in that case.
 * If the string converted to a number
 * exceed that ammount of bytes, the parser cannot ensure that the destination
 * is big enough to fit that value therefore returning an error
 * instead of truncate it. For extracing a value of the list, a function is
 * available with three parameters:
 * 1. the origin of the list to skip the element after the extraction.
 * 2. minimum value allowed.
 * 3. maximum value allowed.
 * If the given number exceed that constrain,
 * an error message is printed by default.
 */
int	ft_parsing(t_scene *scene, const char *file_scene)
{
	const char	*data;
	long		eol;

	if (!end_with(file_scene, ".rt"))
		return (ft_err(ERR_FILE_EXT, 0), -1);
	eol = 0;
	data = read_file(file_scene);
	ft_memset(scene, 0, sizeof(scene));
	// redo that check as it is not safe (buffer overflows)
	while (*data)
	{
		while (*data && (*data == '\n' || *data == '\t' || *data == ' '))
			data++;
		eol = ft_strchr(data, '\n') - data;
		ft_parse_line(scene, data, eol);
		data += eol;
	}
	return (0);
}
