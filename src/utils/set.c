/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:44:35 by tstephan          #+#    #+#             */
/*   Updated: 2025/03/01 11:40:19 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_split(char **split)
{
	int		pos;

	pos = 0;
	while (split[pos])
	{
		free(split[pos]);
		pos++;
	}
	free(split);
}

bool	is_in_stringset(const char *input, const char *stringset, char delim)
{
	char	**set;
	int		pos;
	int		len;

	set = ft_split(stringset, delim);
	pos = 0;
	while (set[pos])
	{
		if (ft_strncmp(input, set[pos], ft_strlen(set[pos])) == 0)
		{
			len = ft_strlen(set[pos]);
			free_split(set);
			return (len);
		}
		pos++;
	}
	free_split(set);
	return (0);
}

bool	is_in_charset(char c, const char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (true);
		charset++;
	}
	return (false);
}
