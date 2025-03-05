/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:05:54 by tstephan          #+#    #+#             */
/*   Updated: 2025/03/05 20:22:58 by tstephan         ###   ########.fr       */
/*   Updated: 2025/03/04 16:35:23 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <unistd.h>
# include <stdbool.h>

# include "../libft/includes/libft.h"

# define QUOTE "\'\""
# define OPERATOR_S "<>;|&{}!" 
# define OPERATOR_M "<<-,&&,||,;;,<<,>>,<&,>&,<>,>|"
# define RESERVED "if,then,else,elif,fi,done,do,case,esac,while,until,for,in,!!"
# define SUBSTITUTE "$((,$(,)),)"

# define HEREDOC_PARSE_ERROR 1
# define HEREDOC_SIGINT 2

typedef enum e_quote
{
	UQUOTE,
	SQUOTE,
	DQUOTE
}	t_quote;

typedef enum e_token_type
{
	T_OPERATOR,
	T_WORD,
	T_QUOTE,
	T_EXPANSION,
	T_COMMENT,
	T_HEREDOC,
	T_BLANK,
	T_RESERVED,
	T_SUBSTITUTE
}	t_token_type;

typedef enum e_node_type
{
	NODE_WORD,
	NODE_REDIR,
	NODE_PIPE,
	NODE_LOGICAL
}	t_node_type;

typedef enum e_redirect_type
{
	REDIR_INPUT,
	REDIR_TRUNC,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redirect_type;

typedef struct s_token
{
	char			*content;
	t_token_type	token_type;
}	t_token;

typedef struct s_cmd
{
	char			**args;
	t_redirect_type	redirect_type;
	int				infile;
	int				outfile;
}	t_cmd;

typedef struct s_tree	t_tree;
typedef struct s_tree
{
	t_node_type		type;
	t_cmd			*cmd;
	t_tree			*left;
	t_tree			*right;
}	t_tree;

void	ft_set_sigaction(void);
bool	handle_sigint(void);

char	*ft_strndup(const char *s, size_t n);
char	*ft_strreplace(const char *full, const char *old, const char *ne);

bool	ft_isspace(char c);

int		ft_getmax(int a, int b);

int		ft_isin_stringset(const char *input, const char *stringset, char delim);
bool	ft_isin_charset(char c, const char *charset);

void	ft_lstclear_string(void *content);
void	ft_lstprint_string(t_list *lst, const char *s);
void	ft_lstclear_t_token(void *content);
void	ft_lstprint_tokens(t_list *lst, const char *s);

int		ft_handle_heredocs(t_list **lst);

t_list	*ft_lex(const char *cmd_line);
t_list	*ft_doom_split(const char *input);
t_list	*ft_remove_whitespace(t_list *lst);
t_token	*ft_remove_quote(t_token *token);
t_token	*ft_expand(t_token *token);
t_list	*ft_fuse_word(t_list *lst);
t_tree	*ft_parse(t_list *tokens);
int		ft_exec(t_tree *root);

#endif
