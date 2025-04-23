/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:48:50 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/23 09:10:05 by tstephan         ###   ########.fr       */
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

static t_token	*particular_expand(t_token *token, t_expand *expand)
{
	int	exit;

	if (ft_strcmp(expand->envvar, "?"))
		expand->envvarrr = ft_itoa(get_shell_pid());
	else
	{
		if (WIFEXITED(g_exit))
			exit = WEXITSTATUS(g_exit);
		else if (WIFSIGNALED(g_exit))
			exit = WTERMSIG(g_exit);
		else if (g_exit & CMD_NOT_FOUND_FLAG)
			exit = 127;
		else
			exit = 11111;
		expand->envvarrr = ft_itoa(exit);
	}
	return (token);
}

static void	expand_exist(t_list *env, t_expand *expand)
{
	expand->envvarr = ft_get_env(env, expand->envvar);
	if (!expand->envvarr)
		expand->envvarrr = "";
	else
		expand->envvarrr = expand->envvarr->value;
}

t_token	*ft_expand(t_list *env, t_token *token)
{
	t_expand	expand;

	if (token->token_type != T_EXPANSION && token->token_type != T_WORD
		&& token->token_type != T_HEREDOC)
		return (token);
	if (ft_find_expand(&expand, token))
		return (token);
	expand.mem = token->content;
	expand.envname = ft_strndup(expand.find, expand.size);
	expand.envvar = ft_strndup(expand.find + 1, expand.size - 1);
	if (ft_strcmp(expand.envvar, "?") == 0
		|| ft_strcmp(expand.envvar, "$") == 0)
		particular_expand(token, &expand);
	else
		expand_exist(env, &expand);
	token->content = ft_strreplace(expand.mem, expand.envname, expand.envvarrr);
	free(expand.mem);
	free(expand.envname);
	free(expand.envvar);
	ft_expand(env, token);
	return (token);
}
