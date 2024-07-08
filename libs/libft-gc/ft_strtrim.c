/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jullopez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:44:17 by jullopez          #+#    #+#             */
/*   Updated: 2024/02/23 23:41:21 by Julien Lopez     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft-gc.h"

static int	ft_is_sep(char const c, char const *sep)
{
	while (*sep)
		if (c == *sep++)
			return (c);
	return (0);
}

char	*ft_strtrim(char const *str, char const *sep)
{
	char	*string;
	size_t	i;

	if (!str || !sep)
		return (NULL);
	i = 0;
	while (ft_is_sep(*str, sep))
		str++;
	if (!*str)
		return (gc_calloc(sizeof(char)));
	i += ft_strlen(str) - 1;
	while (ft_is_sep(*(str + i), sep))
		i--;
	string = (char *) malloc((i += 2) * sizeof(char));
	if (string == NULL)
		return (NULL);
	ft_strlcpy(string, str, i);
	return (string);
}
