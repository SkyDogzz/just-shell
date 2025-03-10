/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:50:05 by tstephan          #+#    #+#             */
/*   Updated: 2025/03/10 14:50:26 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	char	*mem;
	char	*rest;

	while (!ft_quote_ended(input))
	{
		if (handle_sigint())
		{
			free(input);
			return (NULL);
		}
		mem = ft_strjoin(input, "\n");
		free(input);
		rest = readline("> ");
		if (!rest)
		{
			free(mem);
			return (NULL);
		}
		input = ft_strjoin(mem, rest);
		free(mem);
		free(rest);
	}
	return (input);
}
