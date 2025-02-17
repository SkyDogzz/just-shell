/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:23:43 by tstephan          #+#    #+#             */
/*   Updated: 2025/02/17 18:39:53 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_string	*string_create(const char *input)
{
	t_string	*string;

	string = (t_string *)malloc(sizeof(t_string));
	if (!string)
		return (NULL);
	string->content = ft_strdup(input);
	string->next = NULL;
	return (string);
}

t_string	*string_add_bottom(t_string *top, t_string *new_bottom)
{
	t_string	*act;

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

void	string_free(t_string *top)
{
	t_string	*next;

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
