/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:05:21 by tstephan          #+#    #+#             */
/*   Updated: 2025/03/05 19:48:42 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	*ft_quit_heredoc(char *content)
{
	free(content);
	return (NULL);
}

static char	*ft_read_heredoc(char *delimiter)
{
	char	*content;
	char	*input;
	char	*mem;

	content = ft_strdup("");
	while (true)
	{
		if (handle_sigint())
			return (ft_quit_heredoc(content));
		input = readline("heredoc> ");
		if (!input)
			return (ft_quit_heredoc(content));
		if (ft_strncmp(input, delimiter, ft_getmax(ft_strlen(input),
					ft_strlen(delimiter))) == 0)
		{
			free(input);
			break ;
		}
		mem = content;
		content = ft_strjoin(mem, input);
		free(mem);
		free(input);
	}
	return (content);
}

static t_list	*ft_replace_heredoc(t_list *lst, char *content)
{
	t_list	*act;
	t_token	*act_t;
	char	*mem;

	act = lst;
	while (act)
	{
		act_t = act->content;
		if (act_t->token_type == T_OPERATOR && ft_strncmp("<<", act_t->content,
				ft_getmax(ft_strlen(act_t->content), 2)) == 0)
		{
			mem = act_t->content;
			act_t->content = content;
			act_t->token_type = T_HEREDOC;
			act_t = ft_expand(act_t);
			free(mem);
			return (lst);
		}
		act = act->next;
	}
	return (lst);
}

static int	ft_handle_heredoc(t_list *act, t_list **lst)
{
	t_token	*next_t;
	char	*delimiter;
	char	*content;

	if (!act->next)
		return (HEREDOC_PARSE_ERROR);
	next_t = act->next->content;
	if (next_t->token_type == T_BLANK)
	{
		if (!act->next->next)
			return (HEREDOC_PARSE_ERROR);
		next_t = act->next->next->content;
	}
	if (next_t->token_type != T_WORD)
		return (HEREDOC_PARSE_ERROR);
	delimiter = next_t->content;
	content = ft_read_heredoc(delimiter);
	if (!content)
		return (HEREDOC_SIGINT);
	*lst = ft_replace_heredoc(*lst, content);
	return (0);
}

int	ft_handle_heredocs(t_list **lst)
{
	t_list	*act;
	t_token	*act_t;
	int		error;

	act = *lst;
	while (act)
	{
		act_t = act->content;
		if (act_t->token_type == T_OPERATOR
			&& ft_strncmp(act_t->content, "<<", 2) == 0)
		{
			error = ft_handle_heredoc(act, lst);
			if (error)
				return (error);
		}
		act = act->next;
	}
	return (0);
}
