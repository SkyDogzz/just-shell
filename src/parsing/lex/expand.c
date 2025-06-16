/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:48:50 by tstephan          #+#    #+#             */
/*   Updated: 2025/06/16 17:49:00 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_env.h"

static bool	ft_find_expand(t_expand *expand, const t_token *token)
{
	expand->offset = 0;
	while (true)
	{
		expand->find = ft_strchr(token->content + expand->offset, '$');
		if (!expand->find)
			return (true);
		expand->size = 1;
		if (expand->find[expand->size] == '$' || expand->find[expand->size]
			== '?')
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

static t_token	*particular_expand(t_token *token, t_expand *expand, int status)
{
	int	exit;

	printf("status %d\n", status);
	if (ft_strcmp(expand->envvar, "$") == 0)
		expand->envvarrr = ft_itoa(get_shell_pid());
	else if (ft_strcmp(expand->envvar, "?") == 0)
	{
		if (WIFEXITED(status))
			exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit = WTERMSIG(status);
		else if (status & CMD_NOT_FOUND_FLAG)
			exit = 127;
		else if (status & CANT_OPEN_INFILE)
			exit = 1;
		else if (status & CANT_OPEN_OUTFILE)
			exit = 1;
		else
			exit = 0;
		expand->envvarrr = ft_itoa(exit);
	}
	return (token);
}

static void	expand_exist(t_list *env, t_expand *expand)
{
	expand->envvarr = ft_get_env(env, expand->envvar);
	if (!expand->envvarr)
		expand->envvarrr = ft_strdup("");
	else
		expand->envvarrr = ft_strdup(expand->envvarr->value);
}

void	ft_expand_tilde(t_list *env, t_token *token)
{
	char	*find;
	char	*new;

	find = ft_strchr(token->content, '~');
	if (!find)
		return ;
	new = ft_strreplace(token->content, "~", ft_get_env(env, "HOME")->value);
	free(token->content);
	token->content = new;
	ft_expand_tilde(env, token);
}

t_token	*ft_expand(t_list *env, t_token *token, int status)
{
	t_expand	expand;

	if (token->token_type != T_EXPANSION && token->token_type != T_WORD
		&& token->token_type != T_HEREDOC)
		return (token);
	ft_expand_tilde(env, token);
	if (ft_find_expand(&expand, token))
		return (token);
	expand.mem = token->content;
	expand.envname = ft_strndup(expand.find, expand.size);
	expand.envvar = ft_strndup(expand.find + 1, expand.size - 1);
	if (ft_strcmp(expand.envvar, "?") == 0
		|| ft_strcmp(expand.envvar, "$") == 0)
		particular_expand(token, &expand, status);
	else
		expand_exist(env, &expand);
	token->content = ft_strreplace(expand.mem, expand.envname, expand.envvarrr);
	free(expand.mem);
	free(expand.envname);
	free(expand.envvar);
	free(expand.envvarrr);
	ft_expand(env, token, status);
	token->token_type = T_POSTEXPANSION;
	return (token);
}
