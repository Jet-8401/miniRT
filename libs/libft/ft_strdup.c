/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Julien Lopez <marvin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:14:24 by Julien Lopez      #+#    #+#             */
/*   Updated: 2024/02/23 23:41:12 by Julien Lopez     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Description
 * The  strdup() function returns a pointer to a new string
 * which is a duplicate of the string s.
 * Memory for the new string is obtained with malloc(3), and can be freed
 * with free(3).
 *
 * Return Value
 * On success, the strdup() function returns a pointer to the duplicated string.
 * It returns NULL if insufficient memory was available, with errno
 * set to indicate the cause of the error.
 */
char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*copy;

	len = ft_strlen(s) + 1;
	copy = (char *) malloc(len * sizeof(char));
	if (copy == NULL)
		return (copy);
	ft_strlcpy(copy, s, len);
	return (copy);
}
