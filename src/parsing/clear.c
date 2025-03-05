/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:46:58 by tstephan          #+#    #+#             */
/*   Updated: 2025/03/05 17:27:17 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	ft_free(t_list *lst, t_token *token, char *mem)
{
	free(lst);
	free(token->content);
	free(token);
	free(mem);
}

t_list	*ft_fuse_word(t_list *lst)
{
	t_list	*act_l;
	t_list	*mem_l;
	t_token	*act_t;
	t_token	*next_t;
	char	*mem;

	act_l = lst;
	while (act_l && act_l->next)
	{
		act_t = act_l->content;
		next_t = act_l->next->content;
		if (act_t->token_type == T_WORD && next_t->token_type == T_WORD)
		{
			mem = act_t->content;
			act_t->content = ft_strjoin(act_t->content, next_t->content);
			mem_l = act_l->next;
			act_l->next = act_l->next->next;
			ft_free(mem_l, next_t, mem);
			return (ft_fuse_word(lst));
		}
		act_l = act_l->next;
	}
	return (lst);
}
