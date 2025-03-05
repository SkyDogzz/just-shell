/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:48:50 by tstephan          #+#    #+#             */
/*   Updated: 2025/03/05 16:49:47 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_getenv(char *name)
{
	char	*value;

	value = getenv(name);
	if (!value)
		return ("");
	return (value);
}

t_token	*ft_expand(t_token *token)
{
	char	*find;
	char	*mem;
	int		size;
	char	*envname;
	char	*envvar;
	char	*envvarr;
	int		offset;

	if (token->token_type != T_EXPANSION && token->token_type != T_WORD)
		return (token);
	offset = 0;
	while (true)
	{
		find = ft_strchr(token->content + offset, '$');
		if (!find)
			return (token);
		size = 1;
		if (find[size] == '$')
		{
			size++;
			break ;
		}
		while (ft_isalnum(find[size]) || find[size] == '_')
			size++;
		if (size == 1)
		{
			offset = find - token->content + 1;
			continue ;
		}
		break ;
	}
	mem = token->content;
	envname = ft_strndup(find, size);
	envvar = ft_strndup(find + 1, size - 1);
	envvarr = ft_getenv(envvar);
	token->content = ft_strreplace(mem, envname, envvarr);
	free(mem);
	free(envname);
	free(envvar);
	ft_expand(token);
	return (token);
}
