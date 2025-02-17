/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:05:54 by tstephan          #+#    #+#             */
/*   Updated: 2025/02/17 20:18:10 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <unistd.h>

# include "../libft/includes/libft.h"

# define QUOTE "\'\""
# define OPERATOR_S "<>;|&{}!" 
# define OPERATOR_M "<<-,&&,||,;;,<<,>>,<&,>&,<>,>|"
# define RESERVED "if,then,else,elif,fi,done,do,case,esac,while,until,for,in,!!"
# define SUBSTITUTE "$((,$(,)),)"

typedef enum e_quote
{
	UNQUOTED,
	SINGLE_QUOTED,
	DOUBLE_QUOTTED
}	t_quote;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_string	t_string;
typedef struct s_string
{
	char		*content;
	t_string	*next;
}	t_string;

typedef enum e_token_type
{
	REDIRECTION,
	WORDS,
}	t_token_type;

typedef struct s_token	t_token;
typedef struct s_token
{
	char			*content;
	t_token_type	type;
	t_token			*next;
}	t_token;

// Utils
int			is_in_stringset(const char *input, const char *stringset,
				char delim);
t_bool		is_in_charset(char c, const char *charset);

// Signal
void		set_signal_action(void);

// Parse tokens
t_token		*parse_tokens(char *input);

// Tokens utils
t_token		*token_create(char *content, t_token_type type);
t_token		*token_add_bottom(t_token *top, t_token *new_bottom);
void		token_print(t_token *top);
void		token_free(t_token *top);

t_string	*string_create(const char *input);
t_string	*string_add_bottom(t_string *top, t_string *new_bottom);
void		string_free(t_string *top);

#endif
