/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:50:05 by tstephan          #+#    #+#             */
/*   Updated: 2025/06/26 00:37:11 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_quote_ended(const char *input)
{
	t_quote	quote;

	quote = UQUOTE;
	while (*input)
	{
		if (quote == UQUOTE && ft_isin_charset(*input, QUOTE))
		{
			quote = SQUOTE;
			if (*input == '"')
				quote = DQUOTE;
		}
		else if ((quote == DQUOTE && *input == '"' && *(input - 1) != '\\')
			|| (quote == SQUOTE && *input == '\''))
			quote = UQUOTE;
		input++;
	}
	return (quote == UQUOTE);
}

char	*ft_handle_multiline_quote(char *input)
{
	char	*rest;

	while (!ft_quote_ended(input))
	{
		if (handle_sigint())
		{
			free(input);
			return (NULL);
		}
		input = ft_strjoin_free(input, "\n", FIRST);
		rest = ft_readline(PROMPT_QUOTE, NULL, 0);
		if (!rest)
		{
			free(input);
			return (NULL);
		}
		input = ft_strjoin_free(input, rest, BOTH);
	}
	return (input);
}
