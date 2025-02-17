/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:38:09 by tstephan          #+#    #+#             */
/*   Updated: 2025/02/17 18:38:11 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*token_create(char *content, t_token_type type)
{
	t_token	*token;

	if (!content)
		return (NULL);
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = ft_strdup(content);
	token->type = type;
	token->next = NULL;
	return (token);
}

t_token	*token_add_bottom(t_token *top, t_token *new_bottom)
{
	t_token	*act;

	if (!top && !new_bottom)
		return (NULL);
	if (!top)
		return (new_bottom);
	if (!new_bottom)
		return (top);
	act = top;
	while (act->next)
		act = act->next;
	act->next = new_bottom;
	return (top);
}

void	token_print(t_token *top)
{
	if (!top)
		return ;
	while (top)
	{
		printf("Token content '%s' | Token type = %d\n", top->content, top->type);
		top = top->next;
	}
}

void	token_free(t_token *top)
{
	t_token	*next;

	if (!top)
		return ;
	next = top;
	while (next)
	{
		top = next;
		next = next->next;
		free(top->content);
		free(top);
	}
}
