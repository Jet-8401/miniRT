/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Julien Lopez <marvin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:54:04 by Julien Lopez      #+#    #+#             */
/*   Updated: 2024/02/26 09:41:36 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	length;

	i = 0;
	length = ft_strlen(s) + 1;
	while (i < length)
	{
		if (*(s + i) == (unsigned char) c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}
