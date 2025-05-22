/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:46:58 by tstephan          #+#    #+#             */
/*   Updated: 2025/03/26 16:29:44 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_remove_quote(t_token *token)
{
	char	*mem;

	if (token->token_type != T_QUOTE && token->token_type != T_EXPANSION)
		return (token);
	mem = token->content;
	if (token->token_type == T_QUOTE)
		token->content = ft_strtrim(mem, "'");
	else
		token->content = ft_strtrim(mem, "\"");
	free(mem);
	token->token_type = T_WORD;
	return (token);
}

t_list	*ft_fuse_word(t_list *lst)
{
	t_list	*act_l;
	t_list	*mem_l;
	t_token	*act_t;
	t_token	*next_t;

	act_l = lst;
	while (act_l && act_l->next)
	{
		act_t = (t_token *)act_l->content;
		next_t = (t_token *)act_l->next->content;
		if (act_t->token_type == T_WORD && next_t->token_type == T_WORD)
		{
			act_t->content = ft_strjoin_free(act_t->content,
					next_t->content, BOTH);
			mem_l = act_l->next;
			act_l->next = act_l->next->next;
			free(mem_l);
			free(next_t);
			return (ft_fuse_word(lst));
		}
		act_l = act_l->next;
	}
	return (lst);
}
