/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:31:50 by tstephan          #+#    #+#             */
/*   Updated: 2025/03/05 17:41:22 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	int	ft_handle_uquote(const char *input)
{
	int	len;

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
	return (len);
}

static int	ft_handle_quote(const char *input, t_quote *quote)
{
	int	len;
	int	pos;

	len = 1;
	pos = 1;
	while (input[pos] && ((*quote == SQUOTE && input[pos] != '\'')
			|| (*quote == DQUOTE && input[pos] != '"')))
	{
		len++;
		pos++;
	}
	if (input[pos] == '"' || input[pos] == '\'')
		len++;
	*quote = UQUOTE;
	return (len);
}

static void	ft_find_quote(char input, t_quote *quote)
{
	*quote = SQUOTE;
	if (input == '"')
		*quote = DQUOTE;
}

t_list	*ft_doom_split(const char *input)
{
	t_list	*top;
	char	*dup;
	int		len;
	t_quote	quote;

	top = NULL;
	quote = UQUOTE;
	while (input && *input)
	{
		if (!quote && ft_isin_charset(*input, QUOTE))
		{
			ft_find_quote(*input, &quote);
			continue ;
		}
		if (!quote)
			len = ft_handle_uquote(input);
		else
			len = ft_handle_quote(input, &quote);
		dup = ft_strndup(input, len);
		if (!dup)
			continue ;
		ft_lstadd_back(&top, ft_lstnew(dup));
		input += len;
	}
	return (top);
}
