/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:05:54 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/25 20:07:59 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>

# ifdef USE_CUSTOM_RL
#  include "ft_readline.h"
# else
#  include <readline/history.h>
#  include <readline/readline.h>
# endif

# include <stdbool.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>

# include "../libft/includes/libft.h"
# include "ft_env.h"

# define CMD_NOT_FOUND_FLAG 0x10000

# define NC		"\1\e[0m\2"
# define BOLD	"\1\e[1m\2"
# define RED	"\1\e[31m\2"
# define GREEN	"\1\e[32m\2"
# define YELLOW	"\1\e[33m\2"
# define ORANGE	"\1\e[34m\2"
# define PURPLE	"\1\e[35m\2"
# define CYAN	"\1\e[36m\2"

# define QUOTE "\'\""
# define OPERATOR_S "<>;|&{}!"
# define OPERATOR_M "<<-,&&,||,;;,<<,>>,<&,>&,<>,>|"
# define RESERVED "if ,then ,else ,elif ,fi ,\
	done ,do ,case ,esac ,while ,until ,for ,in ,!!"
/*# define SUBSTITUTE "$((,$(,)),),`"*/
# define SUBSTITUTE "$(,),`"

# define HEREDOC_PARSE_ERROR 1
# define HEREDOC_SIGINT 2

extern int	g_exit;

typedef enum e_joinfree
{
	NONE,
	FIRST,
	SECOND,
	BOTH
}	t_joinfree;

typedef enum e_quote
{
	UQUOTE,
	SQUOTE,
	DQUOTE
}						t_quote;

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
}						t_node_type;

typedef enum e_redirect_type
{
	REDIR_INPUT,
	REDIR_TRUNC,
	REDIR_APPEND,
	REDIR_HEREDOC
}						t_redirect_type;

typedef struct s_prompt_info
{
	size_t		prompt_len;
	const char	*user;
	const char	*host;
	const char	*path;
	const char	*last_exit;
}			t_prompt_info;

typedef struct s_token
{
	char			*content;
	t_token_type	token_type;
}	t_token;

typedef struct s_subshell
{
	t_list	*act;
	t_token	*act_t;
	int		level;
	t_list	*pre;
	t_list	*post;
	char	*input;
}	t_subshell;

typedef struct s_redir
{
	char			*file;
	t_redirect_type	type;
}	t_redir;

typedef struct s_cmd
{
	char	**args;
	t_list	*redir;
}	t_cmd;

#endif
