/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:27:54 by jullopez          #+#    #+#             */
/*   Updated: 2024/09/11 14:27:28 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/bonus_header/minirt.h"

int	ft_isspace(char c)
{
	return (c == '\t' || c == ' ');
}

void	free_double_array(char **split)
{
	(void)split;
}

char	*strs_join(const char **strs)
{
	unsigned long	n;
	long			i;
	long			bytes;
	t_lst			*list;
	char			*string;

	i = -1;
	bytes = 0;
	list = NULL;
	while (strs[++i])
	{
		n = ft_strlen(strs[i]);
		list = lst_append(&list, lst_new((void *)n));
		bytes += n;
	}
	string = gc_calloc((bytes + 1) * sizeof(char));
	if (!string)
		return (NULL);
	while (i-- > 0)
	{
		bytes -= (long)list->content;
		ft_memcpy(&string[bytes], strs[i], (long)list->content);
		lst_trunc(&list);
	}
	return (string);
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
	return (i);
}
