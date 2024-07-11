/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:15:48 by jullopez          #+#    #+#             */
/*   Updated: 2024/07/11 13:01:48 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

/*char	*read_file(const char *file)
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
*/

int	ft_isspace(char c)
{
	return (c == '\t' || c == ' ');
}

int	ft_parse_line(t_scene *scene, const char *line)
{
	static char	*identifiers[6] = {"A", "C", "L", "sp", "pl", "cy"};
	int			id;
	long		id_len;

	static int (*functions[6])(t_scene *, char **) = {ambient_init, camera_init,
		light_init, sphere_init, plane_init, cylinder_init};
	id = -1;
	scene->ambient->flag = 0;
	scene->cam->flag = 0;
	scene->light->flag = 0;
	while (++id < 6)
	{
		id_len = ft_strlen(identifiers[id]);
		if (ft_strncmp(identifiers[id], line, id_len) == 0
			&& ft_isspace(line[id_len]))
			return ((*functions)(scene, ft_split(line, "\t ")), 0);
	}
	while (ft_isspace(*line))
		line++;
	if (*line != 0 && *line != '\n')
		return (ft_err("Syntax file error", 0), -1);
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
	int		fd;
	char	*line;
	long	lines_c;

	if (!end_with(file_scene, ".rt"))
		return (ft_err(ERR_FILE_EXT, 0), -1);
	fd = open(file_scene, O_RDONLY);
	if (fd == -1)
		return (ft_err(file_scene, 1), -1);
	ft_memset(scene, 0, sizeof(scene));
	lines_c = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_parse_line(scene, line) == -1)
			return (-1);
		gc_free(line);
		lines_c++;
		line = get_next_line(fd);
	}
	return (0);
}
