/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:36:22 by tstephan          #+#    #+#             */
/*   Updated: 2025/03/05 16:23:29 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*ft_doom_split(const char *input)
{
	t_list	*top;
	char	*dup;
	int		len;
	t_quote	quote;
	int		pos;

	top = NULL;
	quote = UQUOTE;
	while (input && *input)
	{
		if (!quote && ft_isin_charset(*input, QUOTE))
		{
			quote = SQUOTE;
			if (*input == '"')
				quote = DQUOTE;
			continue ;
		}
		if (!quote)
		{
			len = ft_isin_stringset(input, OPERATOR_M, ',');
			if (!len)
				len = ft_isin_stringset(input, RESERVED, ',');
			if (!len)
				len = ft_isin_stringset(input, SUBSTITUTE, ',');
			if (!len)
				len = ft_isin_charset(*input, OPERATOR_S);
			if (!len)
			{
				while (input[len] && !ft_isspace(input[len])
					&& !ft_isin_charset(input[len], QUOTE))
					len++;
			}
			if (!len)
				len = 1;
		}
		else if (quote)
		{
			len = 1;
			pos = 1;
			while (input[pos] && ((quote == SQUOTE && input[pos] != '\'')
					|| (quote == DQUOTE && input[pos] != '"')))
			{
				len++;
				pos++;
			}
			if (input[pos] == '"' || input[pos] == '\'')
				len++;
			quote = UQUOTE;
		}
		dup = ft_strndup(input, len);
		if (!dup)
			continue ;
		ft_lstadd_back(&top, ft_lstnew(dup));
		input += len;
	}
	if (!top)
		return (NULL);
	return (top);
}

static t_token_type	ft_gettype(char *s)
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

static char	*ft_getenv(char *name)
{
	char	*value;

	value = getenv(name);
	if (!value)
		return ("");
	return (value);
}

static t_token	*ft_expand(t_token *token)
{
	char	*find;
	char	*mem;
	int		size;
	char	*envname;
	char	*envvar;
	char	*envvarr;
	int		offset;

	if (token->token_type != T_EXPANSION && token->token_type != T_WORD)
		return (token);
	offset = 0;
	while (true)
	{
		find = ft_strchr(token->content + offset, '$');
		if (!find)
			return (token);
		size = 1;
		if (find[size] == '$')
		{
			size++;
			break ;
		}
		while (ft_isalnum(find[size]) || find[size] == '_')
			size++;
		if (size == 1)
		{
			offset = find - token->content + 1;
			continue ;
		}
		break ;
	}
	mem = token->content;
	envname = ft_strndup(find, size);
	envvar = ft_strndup(find + 1, size - 1);
	envvarr = ft_getenv(envvar);
	token->content = ft_strreplace(mem, envname, envvarr);
	free(mem);
	free(envname);
	free(envvar);
	ft_expand(token);
	return (token);
}

t_list	*ft_lex(const char *input)
{
	t_list	*tokens;
	t_list	*pre_tokens;
	t_list	*act;
	t_token	*dup;

	pre_tokens = ft_doom_split(input);
	if (!pre_tokens)
		return (NULL);
	pre_tokens = ft_remove_whitespace(pre_tokens);
	tokens = NULL;
	act = pre_tokens;
	while (act)
	{
		dup = NULL;
		dup = malloc(sizeof(t_token));
		if (!dup)
			return (tokens);
		dup->content = ft_strdup(act->content);
		dup->token_type = ft_gettype(dup->content);
		dup = ft_expand(dup);
		if (ft_strncmp(dup->content, "", ft_strlen(dup->content) != 0))
			ft_lstadd_back(&tokens, ft_lstnew(dup));
		else
		{
			free(dup->content);
			free(dup);
		}
		act = act->next;
	}
	ft_lstprint_string(pre_tokens, "Print strings :");
	ft_lstclear(&pre_tokens, ft_lstclear_string);
	return (tokens);
}
