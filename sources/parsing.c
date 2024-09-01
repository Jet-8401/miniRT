/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:15:48 by jullopez          #+#    #+#             */
/*   Updated: 2024/09/02 00:17:17 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

int	parser_check_capitals(const char *line)
{
	static char	capitals[25];

	if (line[0] >= 'A' && line[0] <= 'Z' && (!line[0] || ft_isspace(line[0])))
	{
		if (capitals[line[0] - 'A'])
			return (parser_error(ERR_MULTIPLE_IDENTIFIERS), -1);
		capitals[line[0] - 'A'] = line[0];
	}
	return (0);
}

int (*check_identifiers(const char *line))(t_scene *n, char **split)
{
	static char	*identifiers[6] = {"A", "C", "L", "sp", "pl", "cy"};
	static int	(*functions[6])(t_scene *, char **) = {ambient_init,
		camera_init, light_init, sphere_init, plane_init, cylinder_init};
	int			id;
	long		id_len;

	id = 0;
	while (id < 6)
	{
		id_len = ft_strlen(identifiers[id]);
		if (ft_strncmp(identifiers[id], line, id_len) == 0
			&& ft_isspace(line[id_len]))
			return (functions[id]);
		id++;
	}
	return (NULL);
}

int	ft_parse_line(t_scene *scene, const char *line)
{
	int			(*initiator)(t_scene * n, char **);
	int			result;
	char		**split;

	if (parser_check_capitals(line) == -1)
		return (-1);
	initiator = check_identifiers(line);
	if (initiator != NULL)
	{
		split = ft_split(line, "\t\n ");
		result = initiator(scene, split);
		return (free_double_array(split), result);
	}
	while (ft_isspace(*line))
		line++;
	if (*line != 0 && *line != '\n')
		return (parser_error(ERR_UNKNOWN_ID), -1);
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
	int		lines_c;

	if (!end_with(file_scene, ".rt"))
		return (ft_err(ERR_FILE_EXT, 0), -1);
	fd = open(file_scene, O_RDONLY);
	if (fd == -1)
		return (ft_err(file_scene, 1), -1);
	ft_memset(scene, 0, sizeof(t_scene));
	init_pointer_objects(scene);
	lines_c = 1;
	line = get_next_line(fd);
	while (line != NULL)
	{
		parser_err_line(lines_c);
		if (ft_parse_line(scene, line) == -1)
			return (-1);
		gc_free(line);
		lines_c++;
		line = get_next_line(fd);
	}
	return (ft_check_scene(scene));
}

int ft_check_scene(t_scene *scene)
{
	if (!scene->cam)
		return (ft_err("You must add a camera into the scene", 0), -1);
	if (!scene->ambient)
		return (ft_err("You must add an ambient lighting", 0), -1);
	if (!scene->plane && !scene->sphere && !scene->cylinder)
		return (ft_err("You must add at least one object", 0), -1);
	return (0);
}

