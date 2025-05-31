/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_helper2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:37:21 by tstephan          #+#    #+#             */
/*   Updated: 2025/03/14 14:01:05 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstprint_pipes(t_list *lst, const char *s)
{
	t_list	*act;

	printf("%s\n", s);
	while (lst)
	{
		act = lst->content;
		ft_lstprint_tokens(act, "Tokens");
		lst = lst->next;
	}
	(void) lst;
}

void	ft_lstclear_pipes(void *content)
{
	t_list	*list;

	if (!content)
		return ;
	list = content;
	ft_lstclear(&list, ft_lstclear_t_token);
}
