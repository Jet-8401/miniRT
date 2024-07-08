/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Julien Lopez <marvin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:30:26 by Julien Lopez      #+#    #+#             */
/*   Updated: 2024/02/26 09:43:42 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft-gc.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dst_len)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dst_len < 1)
		return (src_len);
	i = 0;
	while (i < (dst_len - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (src_len);
}
