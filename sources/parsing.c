/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jullopez <jullopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:15:48 by jullopez          #+#    #+#             */
/*   Updated: 2024/07/09 18:05:13 by jullopez         ###   ########.fr       */
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
		gc_free(old);
		bytes = read(fd, buffer, READ_BUF_SIZE - 1);
	}
	return (data);
}

int	ft_parsing(t_scene *scene, const char *file_scene)
{
	const char *data;

	if (!end_with(file_scene, ".rt"))
		return (ft_err(ERR_FILE_EXT, 0), -1);
	data = read_file(file_scene);
	if (!data)
		return (-1);
	printf("{%s}", data);
	(void) scene;
	return (0);
}
