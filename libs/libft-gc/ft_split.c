/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jullopez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:11:45 by jullopez          #+#    #+#             */
/*   Updated: 2024/07/10 15:44:32 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft-gc.h"

#include <stdio.h>

static int	ft_is_sep(char const *s, char const *sep)
{
	long	i;

	i = -1;
	while (sep[++i])
		if (*s != sep[i] && (*(s + 1) == sep[i] || *(s + 1) == 0))
			return (1);
	return (0);
}

static size_t	count_words(char const *s, char const *sep)
{
	size_t	words;

	words = 0;
	while (*s)
		if (ft_is_sep(s++, sep))
			words++;
	return (words);
}

char	**ft_split(char const *s, char *sep)
{
	size_t	lsep;
	char	**strings;
	size_t	i;
	size_t	words;

	if (!s)
		return (NULL);
	i = 0;
	words = 0;
	lsep = 0;
	strings = (char **) gc_calloc((count_words(s, sep) + 1) * sizeof(char *));
	if (strings == NULL)
		return (NULL);
	while (s[i])
	{
		if (ft_is_sep(s + i, sep))
			strings[words++] = ft_substr(s, lsep, i + 1 - lsep);
		if (ft_is_sep(&s[i], sep))
			lsep = i + 1;
		i++;
	}
	return (strings);
}
