/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:05:54 by tstephan          #+#    #+#             */
/*   Updated: 2025/02/24 17:18:39 by yandry           ###   ########.fr       */
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
	T_BLANK
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
	t_cmd			cmd;
	t_tree			*left;
	t_tree			*right;
}	t_tree;

void	ft_set_sigaction(void);

t_list	*ft_lex(const char *cmd_line);
t_tree	*ft_parse(t_list *tokens);
int		ft_exec(t_tree *root);

#endif
