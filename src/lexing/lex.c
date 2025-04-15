/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:36:22 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/15 15:03:37 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	handle_heredoc_error(t_list **tokens)
{
	int	error;

	error = ft_handle_heredocs(tokens);
	if (error)
	{
		if (error == HEREDOC_PARSE_ERROR)
		{
			printf("Syntax error near unexpected token\n");
			ft_lstclear(tokens, ft_lstclear_t_token);
			return (true);
		}
		if (error == HEREDOC_SIGINT)
		{
			ft_lstclear(tokens, ft_lstclear_t_token);
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

static char	*check_tokens(t_list *tokens)
{
	t_token	*token;
	int		prev;

	if (!tokens)
		return (NULL);
	token = (t_token *)tokens->content;
	if (token->token_type == T_OPERATOR_S && ft_strcmp(token->content, ";") != 0)
		return (token->content);
	token = ft_lstlast(tokens)->content;
	if (token->token_type == T_OPERATOR_S && ft_strcmp(token->content, ";") != 0)
		return (token->content);
	token = (t_token *)tokens->content;
	prev = 0;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (prev == 1 && token->token_type == T_OPERATOR_S)
			return (token->content);
		if (token->token_type == T_OPERATOR_S)
			prev = 1;
		else
			prev = 0;
		tokens = tokens->next;
	}
	return (NULL);
}

t_list	*ft_lex(const char *input)
{
	t_list	*tokens;
	t_list	*pre_tokens;
	char	*unexpected;

	pre_tokens = ft_doom_split(input);
	if (!pre_tokens)
		return (NULL);
	pre_tokens = ft_remove_whitespace(pre_tokens);
	tokens = NULL;
	tokens = ft_string_to_token(tokens, pre_tokens);
	ft_lstclear(&pre_tokens, ft_lstclear_string);
	tokens = ft_fuse_word(tokens);
	if (handle_heredoc_error(&tokens))
		return (NULL);
	tokens = ft_remove_spaces(tokens);
	unexpected = check_tokens(tokens);
	if (unexpected)
	{
		printf("Syntax error near unexpected token \"%s\"\n", unexpected);
		ft_lstclear(&tokens, ft_lstclear_t_token);
		return (NULL);
	}
	return (tokens);
}
