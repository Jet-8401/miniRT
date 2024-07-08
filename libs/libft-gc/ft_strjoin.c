/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jullopez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:15:11 by jullopez          #+#    #+#             */
/*   Updated: 2024/02/26 09:42:42 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft-gc.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*string;
	size_t	i;
	size_t	first;
	size_t	second;

	if (!s1 || !s2)
		return (NULL);
	first = ft_strlen(s1);
	second = ft_strlen(s2);
	string = (char *) gc_calloc((first + second + 1) * sizeof(char));
	if (string == NULL)
		return (string);
	i = first;
	while (i-- != 0)
		*(string + i) = *(s1 + i);
	i = second;
	while (i-- != 0)
		*(string + first + i) = *(s2 + i);
	return (string);
}
