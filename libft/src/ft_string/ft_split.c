/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:58:25 by yandry            #+#    #+#             */
/*   Updated: 2024/12/11 13:46:24 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	ft_count_words(const char *s, char sep)
{
	size_t	words;

	words = 0;
	while (*s)
	{
		if (*s != sep && (*(s + 1) == sep || *(s + 1) == '\0'))
			words++;
		s++;
	}
	return (words);
}

static void	ft_write_elem(char *new, const char *s, char sep)
{
	while (*s && *s != sep)
		*new++ = *s++;
	*new = '\0';
}

static void	ft_sinistre(char **array, size_t last_index)
{
	size_t	i;

	i = 0;
	while (i < last_index)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static char	**set_array(char **array, const char *s, char sep)
{
	size_t		i;
	const char	*start;

	i = 0;
	while (*s)
	{
		while (*s == sep)
			s++;
		if (!*s)
			break ;
		start = s;
		while (*s && *s != sep)
			s++;
		array[i] = malloc(sizeof(char) * (s - start + 1));
		if (!array[i])
		{
			ft_sinistre(array, i);
			return (NULL);
		}
		ft_write_elem(array[i], start, sep);
		i++;
	}
	array[i] = 0;
	return (array);
}

char	**ft_split(const char *s, char c)
{
	size_t	words;
	char	**array;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	array = malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	array = set_array(array, s, c);
	return (array);
}
