/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:48:50 by tstephan          #+#    #+#             */
/*   Updated: 2025/03/05 17:14:02 by tstephan         ###   ########.fr       */
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

typedef struct s_expand
{
	char	*find;
	char	*mem;
	int		size;
	char	*envname;
	char	*envvar;
	char	*envvarr;
	int		offset;
}	t_expand;

static bool	ft_find_expand(t_expand *expand, t_token *token)
{
	expand->offset = 0;
	while (true)
	{
		expand->find = ft_strchr(token->content + expand->offset, '$');
		if (!expand->find)
			return (true);
		expand->size = 1;
		if (expand->find[expand->size] == '$')
		{
			expand->size++;
			break ;
		}
		while (ft_isalnum(expand->find[expand->size])
			|| expand->find[expand->size] == '_')
			expand->size++;
		if (expand->size == 1)
		{
			expand->offset = expand->find - token->content + 1;
			continue ;
		}
		break ;
	}
	return (false);
}

t_token	*ft_expand(t_token *token)
{
	t_expand	expand;

	if (token->token_type != T_EXPANSION && token->token_type != T_WORD)
		return (token);
	if (ft_find_expand(&expand, token))
		return (token);
	expand.mem = token->content;
	expand.envname = ft_strndup(expand.find, expand.size);
	expand.envvar = ft_strndup(expand.find + 1, expand.size - 1);
	expand.envvarr = ft_getenv(expand.envvar);
	token->content = ft_strreplace(expand.mem, expand.envname, expand.envvarr);
	free(expand.mem);
	free(expand.envname);
	free(expand.envvar);
	ft_expand(token);
	return (token);
}
