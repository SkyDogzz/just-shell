/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:05:13 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/25 19:38:14 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

# include "minishell.h"

t_list	*ft_string_to_token(t_list *env, t_list *tokens, t_list *pre_tokens);
bool	ft_isspace(char c);
int		ft_isin_stringset(const char *input, const char *stringset, char delim);
bool	ft_isin_charset(char c, const char *charset);
t_list	*ft_doom_split(const char *input);
int		ft_getmax(int a, int b);
char	*ft_strjoin_free(const char *s1, const char *s2, t_joinfree flag);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strreplace(const char *full, const char *old, const char *ne);
bool	ft_is_pipe(const t_token *token);
bool	ft_is_logical(const t_token *token);
bool	is_operator(const t_token *token, const char *op);
char	*random_filename(void);

#endif
