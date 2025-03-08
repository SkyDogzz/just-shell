/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:05:54 by tstephan          #+#    #+#             */
/*   Updated: 2025/03/01 15:36:16 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <unistd.h>

# define NC		"\e[0m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"

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
}						t_quote;

typedef enum e_token_type
{
	T_OPERATOR_S,
	T_OPERATOR_M,
	T_WORD,
	T_QUOTE,
	T_EXPANSION,
	T_COMMENT,
	T_HEREDOC,
	T_BLANK
}						t_token_type;

typedef enum e_node_type
{
	NODE_WORD,
	NODE_REDIR,
	NODE_PIPE,
	NODE_LOGICAL
}						t_node_type;

typedef enum e_redirect_type
{
	REDIR_INPUT,
	REDIR_TRUNC,
	REDIR_APPEND,
	REDIR_HEREDOC
}						t_redirect_type;

typedef struct s_token
{
	char				*content;
	t_token_type		token_type;
}						t_token;

typedef struct s_cmd
{
	char				**args;
	t_redirect_type		redirect_type;
	int					infile;
	int					outfile;
}						t_cmd;

typedef struct s_tree	t_tree;
typedef struct s_tree
{
	t_node_type			type;
	t_cmd				*cmd;
	t_tree				*left;
	t_tree				*right;
}						t_tree;

void					ft_set_sigaction(void);

t_list					*ft_lex(const char *cmd_line);
t_tree					*ft_parse(const t_list *tokens);
int						ft_exec(t_tree *root);

bool					is_in_charset(const char c, const char *charset);
bool					is_in_stringset(const char *input,
							const char *stringset, char delim);

typedef char			*(*t_readline)(const char *);
t_token					*ft_new_token(const char *content);

void					ft_print_tree(t_tree *root, int level, int is_last);

#endif
