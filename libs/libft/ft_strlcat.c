/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Julien Lopez <marvin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:29:22 by Julien Lopez      #+#    #+#             */
/*   Updated: 2024/02/23 16:52:26 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Base code, not optimized for readability, but with less lines */
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;

	i = 0;
	dst_len = 0;
	if (dst == 0 && size == 0)
		return (0);
	while (dst[dst_len] && dst_len < size)
		dst_len++;
	if (dst_len == size)
		return (dst_len + ft_strlen(src));
	while (src[i] && i + dst_len + 1 < size)
	{
		dst[i + dst_len] = src[i];
		i++;
	}
	dst[i + dst_len] = 0;
	while (src[i])
		i++;
	return (dst_len + i);
}

/* Optimized code, don't change the process time */
/*
static size_t ft_strnlen(const char *s, const size_t n)
{
	size_t	i;

	i = 0;
	while (s[i] && i < n)
		i++;
	return (i);
}

size_t  ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strnlen(dst, size);
	src_len = ft_strlen(src);
	if (dst_len == size)
		return (dst_len + src_len);
	if (src_len + dst_len < size)
		ft_memcpy(dst + dst_len, src, src_len + 1);
	else
	{
		ft_memcpy(dst + dst_len, src, size - dst_len - 1);
		dst[size - 1] = 0;
	}
	return (dst_len + src_len);
}
*/
