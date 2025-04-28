/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_to_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:02:11 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/28 16:15:47 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_type	ft_gettype(const char *s)
{
	if (ft_strlen(s) == 1 && ft_isspace(s[0]))
		return (T_BLANK);
	else if (ft_strlen(s) == 1 && ft_isin_charset(s[0], OPERATOR_S))
		return (T_OPERATOR);
	else if (ft_isin_stringset(s, OPERATOR_M, ','))
		return (T_OPERATOR);
	else if (ft_isin_stringset(s, RESERVED, ','))
		return (T_RESERVED);
	else if (ft_isin_stringset(s, SUBSTITUTE, ','))
		return (T_SUBSTITUTE);
	else if (s[0] == '\'')
		return (T_QUOTE);
	else if (s[0] == '"')
		return (T_EXPANSION);
	return (T_WORD);
}

static bool	create_token(t_list **tokens, struct dirent *file)
{
	t_token			*new;
	t_token			*new_space;

	new = (t_token *)malloc(sizeof(t_token));
	new_space = (t_token *)malloc(sizeof(t_token));
	if (!new || !new_space)
		return (false);
	new->content = ft_strdup(file->d_name);
	new->token_type = T_WORD;
	ft_lstadd_back(tokens, ft_lstnew(new));
	new_space->content = ft_strdup(" ");
	new_space->token_type = T_BLANK;
	ft_lstadd_back(tokens, ft_lstnew(new_space));
	return (true);
}

bool	ft_expand_wildcard(t_list **tokens, t_token *dup)
{
	DIR				*dir;
	struct dirent	*file;

	if (dup->token_type != T_WORD || strcmp(dup->content, "*") != 0)
		return (false);
	dir = opendir(".");
	if (!dir)
		return (false);
	file = readdir(dir);
	while (file)
	{
		if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0)
		{
			file = readdir(dir);
			continue ;
		}
		if (!create_token(tokens, file))
		{
			closedir(dir);
			return (false);
		}
		file = readdir(dir);
	}
	closedir(dir);
	return (true);
}

static void	ft_expand_utils(t_list *env, t_list **tokens, t_list *act)
{
	t_token	*dup;

	dup = malloc(sizeof(t_token));
	if (!dup)
		return ;
	dup->content = ft_strdup(act->content);
	dup->token_type = ft_gettype(dup->content);
	if (ft_expand_wildcard(tokens, dup))
	{
		free(dup->content);
		free(dup);
		return ;
	}
	dup = ft_expand(env, dup);
	dup = ft_remove_quote(dup);
	if (ft_strcmp(dup->content, "") != 0)
		ft_lstadd_back(tokens, ft_lstnew(dup));
	else
	{
		free(dup->content);
		free(dup);
	}
}

t_list	*ft_string_to_token(t_list *env, t_list *tokens, t_list *pre_tokens)
{
	t_list	*act;

	act = pre_tokens;
	while (act)
	{
		ft_expand_utils(env, &tokens, act);
		act = act->next;
	}
	return (tokens);
}
