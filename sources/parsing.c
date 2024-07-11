/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:15:48 by jullopez          #+#    #+#             */
/*   Updated: 2024/07/11 17:19:47 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

int	(*check_identifiers(const char *line))(t_scene *n, char **split)
{
	static char	*identifiers[6] = {"A", "C", "L", "sp", "pl", "cy"};
	static int	(*functions[6])(t_scene *, char **) = {ambient_init,
		camera_init, light_init, sphere_init, plane_init, cylinder_init};
	int			id;
	long		id_len;

	id = -1;
	while (identifiers[++id])
	{
		id_len = ft_strlen(identifiers[id]);
		printf("id=%p\n",(void *) functions[id]);
		printf("letter=%s\n", identifiers[id]);
		if (ft_strncmp(identifiers[id], line, id_len) == 0
			&& ft_isspace(line[id_len]))
			return (functions[id]);
	}
	return (NULL);
}

int	ft_parse_line(t_scene *scene, const char *line, long line_c)
{
	int		(*initiator)(t_scene *n, char**);
	int		result;
	char	**split;

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
		return (parser_error(line_c, 0, ERR_UNKNOWN_ID), -1);
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
	ft_memset(scene, 0, sizeof(t_scene));
	lines_c = 1;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_parse_line(scene, line, lines_c) == -1)
			return (-1);
		gc_free(line);
		lines_c++;
		line = get_next_line(fd);
	}
	return (0);
}
