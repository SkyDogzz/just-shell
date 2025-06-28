/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:36:22 by tstephan          #+#    #+#             */
/*   Updated: 2025/06/28 18:15:35 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	handle_heredoc_error(t_list *env, t_list **tokens, int *status)
{
	int	error;

	error = ft_handle_heredocs(env, tokens, status);
	if (error)
	{
		if (error == HEREDOC_PARSE_ERROR)
		{
			ft_dprintf(STDERR_FILENO, SYNTAX_ERROR_PROMPT, "<<");
			ft_lstclear(tokens, ft_lstclear_t_token);
			*status = 2 | SYNTAX_ERROR;
			return (true);
		}
		if (error == HEREDOC_SIGINT)
		{
			ft_lstclear(tokens, ft_lstclear_t_token);
			*status = SIGINT;
			return (true);
		}
	}
	return (false);
}

static t_list	*ft_remove_spaces(t_list *tokens)
{
	t_list	*act;
	t_token	*act_t;
	t_list	*mem;

	act = tokens;
	while (act && act->next)
	{
		act_t = act->next->content;
		if (act_t->token_type == T_BLANK)
		{
			mem = act->next;
			act->next = act->next->next;
			ft_lstclear_t_token(mem->content);
			free(mem);
		}
		act = act->next;
	}
	return (tokens);
}

static char	*check_tokens(t_list *tokens, int *status)
{
	t_token	*tok;

	if (!tokens)
		return (NULL);
	*status = 2 | SYNTAX_ERROR;
	tok = (t_token *)ft_lstlast(tokens)->content;
	if (tok->token_type == T_OPERATOR && ft_strcmp(tok->content, ";") != 0)
		return (tok->content);
	tok = (t_token *)tokens->content;
	if (tok->token_type == T_OPERATOR && ft_strcmp(tok->content, "<") != 0)
		return (tok->content);
	while (tokens->next)
	{
		tok = (t_token *)tokens->content;
		if (tok->token_type == T_OPERATOR
			&& ((t_token *)tokens->next->content)->token_type == T_OPERATOR)
			return (tok->content);
		tokens = tokens->next;
	}
	*status = 0;
	return (NULL);
}

static char	*check_subshell(t_list *tokens, char *unexpected)
{
	char	*prev;

	if (unexpected)
		return (unexpected);
	if (!tokens)
		return (NULL);
	prev = ((t_token *)(tokens->content))->content;
	tokens = tokens->next;
	while (tokens)
	{
		if (ft_strcmp(prev, ")") == 0
			&& ft_strcmp(((t_token *)(tokens->content))->content, "(") == 0)
			return (prev);
		prev = ((t_token *)(tokens->content))->content;
		tokens = tokens->next;
	}
	return (NULL);
}

t_list	*ft_lex(t_list *env, const char *input, int *status)
{
	t_list	*tokens;
	t_list	*pre_tokens;
	char	*unexpected;

	pre_tokens = ft_doom_split(input);
	if (!pre_tokens)
		return (NULL);
	pre_tokens = ft_remove_whitespace(pre_tokens);
	tokens = NULL;
	tokens = ft_string_to_token(env, tokens, pre_tokens, status);
	ft_lstclear(&pre_tokens, ft_lstclear_string);
	tokens = ft_fuse_word(tokens);
	if (handle_heredoc_error(env, &tokens, status))
		return (NULL);
	tokens = ft_remove_spaces(tokens);
	unexpected = check_tokens(tokens, status);
	unexpected = check_subshell(tokens, unexpected);
	if (unexpected)
	{
		ft_dprintf(STDERR_FILENO, SYNTAX_ERROR_PROMPT, unexpected);
		ft_lstclear(&tokens, ft_lstclear_t_token);
		return (NULL);
	}
	return (tokens);
}
