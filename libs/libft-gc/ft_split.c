/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jullopez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:11:45 by jullopez          #+#    #+#             */
/*   Updated: 2024/02/26 09:41:19 by jullopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft-gc.h"

static int	ft_is_sep(char const *s, char const sep)
{
	return (*s != sep && (*(s + 1) == sep || *(s + 1) == 0));
}

static size_t	count_words(char const *s, char const sep)
{
	size_t	words;

	words = 0;
	while (*s)
		if (ft_is_sep(s++, sep))
			words++;
	return (words);
}

char	**ft_split(char const *s, char c)
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
	strings = (char **) gc_calloc((count_words(s, c) + 1) * sizeof(char *));
	if (strings == NULL)
		return (NULL);
	while (s[i])
	{
		if (ft_is_sep(s + i, c))
			strings[words++] = ft_substr(s, lsep, i + 1 - lsep);
		if (s[i] == c)
			lsep = i + 1;
		i++;
	}
	return (strings);
}
/*
#include <stdio.h>

int	main(void)
{
	char **strings = ft_split("   H e l l o    Wo rld  ", 'o');
	size_t	i = 0;

	while (strings[i])
	{
		printf("%s\n", strings[i]);
		free(strings[i++]);
	}
	free(strings);
	return (0);
}*/
