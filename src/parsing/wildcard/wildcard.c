/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:30:55 by tstephan          #+#    #+#             */
/*   Updated: 2025/06/24 16:51:44 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wildcard.h"
#include "minishell.h"

static bool	create_token(t_list **tokens, struct dirent *file, char *base)
{
	t_token			*new;
	t_token			*new_space;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (false);
	new_space = (t_token *)malloc(sizeof(t_token));
	if (!new_space)
	{
		free(new);
		return (false);
	}
	if (ft_strlen(base) > 1 && base[ft_strlen(base) - 1] == '.')
		base[ft_strlen(base) - 1] = 0;
	new->content = ft_strjoin(base, file->d_name);
	new->token_type = T_WORD;
	ft_lstadd_back(tokens, ft_lstnew(new));
	new_space->content = ft_strdup(" ");
	new_space->token_type = T_BLANK;
	ft_lstadd_back(tokens, ft_lstnew(new_space));
	return (true);
}

static DIR	*open_directory(char *pattern)
{
	DIR	*dir;

	if (ft_strlen(pattern) <= 1)
		dir = opendir(".");
	else
		dir = opendir(pattern);
	return (dir);
}

static bool	skip_file(struct dirent *file, char *base, char *pattern)
{
	if (ft_strcmp(file->d_name, ".") == 0 || ft_strcmp(file->d_name, "..") == 0)
		return (true);
	if (ft_strlen(pattern) > 1 && base[ft_strlen(pattern) - 2] != '.'
		&& file->d_name[0] == '.')
		return (true);
	return (false);
}

static bool	process_files(DIR *dir, t_list **tokens, char *base, char *pattern)
{
	struct dirent	*file;

	file = readdir(dir);
	while (file)
	{
		if (!skip_file(file, base, pattern))
		{
			if (!create_token(tokens, file, base))
				return (false);
		}
		file = readdir(dir);
	}
	return (true);
}

bool	ft_expand_wildcard(t_list **tokens, t_token *dup)
{
	DIR		*dir;
	char	*base;
	bool	success;

	if (ft_strlen(dup->content) <= 0)
		return (false);
	if (!tokens || dup->token_type != T_WORD
		|| dup->content[ft_strlen(dup->content) - 1] != '*')
		return (false);
	base = ft_strndup(dup->content, ft_strlen(dup->content) + 1);
	base[ft_strlen(dup->content) - 1] = 0;
	dir = open_directory(base);
	if (!dir)
	{
		free(base);
		return (false);
	}
	success = process_files(dir, tokens, base, dup->content);
	free(base);
	closedir(dir);
	return (success);
}
