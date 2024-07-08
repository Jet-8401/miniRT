/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jullopez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:19:45 by jullopez          #+#    #+#             */
/*   Updated: 2024/02/22 11:20:09 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft-gc.h"

/* Note for future:
 * Delete ft_strnlen as static and make it global
 * so a lot of function can be more readables.
 */
static size_t	ft_strnlen(const char *s, const size_t n)
{
	size_t	i;

	i = 0;
	while (s[i] && i < n)
		i++;
	return (i);
}

/* Explanation of the function :
 * The function get the raw size of the string and check if 'start'
 * is greater than the raw size.
 * 	If so, it return an empty array of just the null-terminated byte
 * and end the function.
 * 	Else it get the size of (s + start) and add one for the null-
 * terminated byte in 'src_len', calloc the array and copy 's' to 'dst' for
 * 'src_len - 1' chars.
 * Note that there is no need for adding the null-terminated byte manually
 * or by invoking a function like 'ft_strlcpy' that will do it for us
 * because calloc already add the '0' at the end, we just have to make sure
 * to not overwriting it with memcpy (using memcpy is faster).
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	src_len;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (gc_calloc(sizeof(char)));
	src_len = ft_strnlen(s + start, len) + 1;
	dst = gc_calloc(src_len * sizeof(char));
	if (dst == NULL)
		return (NULL);
	ft_memcpy(dst, s + start, src_len - 1);
	return (dst);
}
