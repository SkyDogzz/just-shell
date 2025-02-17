/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:33:55 by yandry            #+#    #+#             */
/*   Updated: 2024/12/11 13:46:24 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*ft_getstart(const char *s, const char *set)
{
	const char	*set_ptr;
	int			in_set;

	while (*s)
	{
		in_set = 0;
		set_ptr = set;
		while (*set_ptr)
		{
			if (*s == *set_ptr)
				in_set = 1;
			set_ptr++;
		}
		if (!in_set)
			return ((char *)s);
		s++;
	}
	return ((char *)s);
}

static char	*ft_getend(const char *s, const char *set, const char *start)
{
	const char	*end;
	const char	*set_ptr;
	int			in_set;

	end = s + ft_strlen(s) - 1;
	while (end >= start)
	{
		in_set = 0;
		set_ptr = set;
		while (*set_ptr)
		{
			if (*end == *set_ptr)
				in_set = 1;
			set_ptr++;
		}
		if (!in_set)
			return ((char *)end);
		end--;
	}
	return ((char *)start);
}

static char	*ft_fillstr(const char *start, const char *end)
{
	char	*n;
	char	*p;
	size_t	len;

	if (start > end)
		return (NULL);
	if (!*start && !*end)
		len = 1;
	else
		len = end - start + 2;
	n = malloc(sizeof(char) * len);
	if (!n)
		return (NULL);
	p = n;
	while (start <= end && (*start && *end))
		*p++ = *start++;
	*p = '\0';
	return (n);
}

static char	*ft_shakal(void)
{
	char	*s;

	s = malloc(sizeof(char) * 1);
	if (!s)
		return (NULL);
	*s = '\0';
	return (s);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*begin;
	char	*end;
	char	*new;

	if (!s1)
		return (ft_shakal());
	begin = ft_getstart(s1, set);
	end = ft_getend(s1, set, begin);
	if (begin > end)
	{
		new = malloc(sizeof(char) * 1);
		if (!new)
			return (NULL);
		*new = '\0';
	}
	else
		new = ft_fillstr(begin, end);
	if (!new)
		return (NULL);
	return (new);
}
