/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:38:29 by tstephan          #+#    #+#             */
/*   Updated: 2025/02/25 18:59:57 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lstclear_string(void *content)
{
	char	*ccontent;

	if (!content)
		return ;
	ccontent = (char *)content;
	free(content);
}

void	ft_lstprint_string(t_list *lst, const char *s)
{
	printf("%s\n", s);
	while (lst)
	{
		printf("string = '%s'\n", (char *)lst->content);
		lst = lst->next;
	}
}

void	ft_lstclear_t_token(void *content)
{
	t_token	*ccontent;

	if (!content)
		return ;
	ccontent = (t_token *)content;
	free(ccontent->content);
}
