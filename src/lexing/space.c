/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:08:18 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/18 16:15:02 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del(void *content)
{
	t_list	*lst;

	lst = (t_list *)content;
	free(lst);
}

t_list	*ft_pretrim(t_list *lst)
{
	t_list	*mem;
	t_list	*act;

	act = lst;
	if (!act)
		return (NULL);
	while (act && act->content && ft_strlen(act->content) == 1
		&& ft_isspace(((char *)act->content)[0]))
	{
		mem = act;
		act = act->next;
		ft_lstdelone(mem, del);
	}
	return (act);
}

t_list	*ft_posttrim(t_list *lst)
{
	t_list	*start;

	start = lst;
	if (!start)
		return (NULL);
	while (lst->next && lst->next->next)
		lst = lst->next;
	if (lst->next && ft_strlen(lst->next->content) == 1
		&& ft_isspace(((char *)lst->next->content)[0]))
	{
		ft_lstdelone(lst->next, del);
		lst->next = NULL;
		start = ft_posttrim(start);
	}
	return (start);
}

t_list	*ft_remove_multispace(t_list *lst)
{
	t_list	*act;
	t_list	*mem;

	act = lst;
	if (!act)
		return (NULL);
	while (act && act->next && act->next->next)
	{
		if (ft_strlen(act->content) == 1 && ft_strlen(act->next->content) == 1
			&& ft_isspace(((char *)act->content)[0])
			&& ft_isspace(((char *)act->next->content)[0]))
		{
			mem = act->next->next;
			ft_lstdelone(act->next, del);
			act->next = mem;
			ft_remove_whitespace(lst);
		}
		act = act->next;
	}
	return (lst);
}

t_list	*ft_remove_whitespace(t_list *lst)
{
	lst = ft_pretrim(lst);
	lst = ft_posttrim(lst);
	lst = ft_remove_multispace(lst);
	return (lst);
}
