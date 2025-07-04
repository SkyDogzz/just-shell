/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:30:21 by tstephan          #+#    #+#             */
/*   Updated: 2025/07/04 18:29:37 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*is_alias(char *line)
{
	if (!line)
		return (NULL);
	while (ft_isspace(*line))
		line++;
	if (*line == '#')
		return (NULL);
	if (ft_strncmp(line, "alias", ft_strlen("alias")))
		return (NULL);
	line += 6;
	while (ft_isspace(*line))
		line++;
	if (!ft_strchr(line, '='))
		return (NULL);
	return (line);
}

t_list	*parse_alias(t_list *alias, char *line)
{
	t_alias	*new;
	char	*name;
	char	*value;
	char	**split;

	line = is_alias(line);
	if (!line)
		return (alias);
	split = ft_split(line, '=');
	if (!split || !split[0])
		return (alias);
	name = ft_strdup(split[0]);
	ft_free_array((void ***)&split);
	value = ft_strdup(ft_strchr(line, '=') + 1);
	if (!name || !value)
		return (alias);
	new = malloc(sizeof(t_alias));
	if (!new)
		return (alias);
	new->name = name;
	new->value = value;
	ft_lstadd_back(&alias, ft_lstnew(new));
	return (alias);
}

void	del_alias(void *content)
{
	t_alias	*alias;

	alias = content;
	free(alias->name);
	free(alias->value);
	free(alias);
}

char	*ft_exec_alias(char *input, t_rc *rc)
{
	t_list	*aliases;
	t_alias	*alias;
	char	*mem;

	if (!rc || !rc->alias)
		return (input);
	aliases = rc->alias;
	while (aliases)
	{
		alias = aliases->content;
		if (ft_strncmp(input, alias->name, ft_strlen(alias->name)) == 0)
		{
			mem = input;
			input = ft_strreplace(mem, alias->name, alias->value);
			free(mem);
		}
		aliases = aliases->next;
	}
	return (input);
}
