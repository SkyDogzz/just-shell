/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:05:54 by tstephan          #+#    #+#             */
/*   Updated: 2025/04/15 18:19:47 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <readline/history.h>

# ifdef USE_CUSTOM_RL
#  include "ft_readline.h"
# else
#  include <readline/readline.h>
# endif

# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>

# include "../libft/includes/libft.h"

# define NC		"\e[0m"
# define BOLD	"\e[1m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define YELLOW	"\e[33m"
# define ORANGE	"\e[34m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"

# define QUOTE "\'\""
# define OPERATOR_S "<>;|&{}!"
# define OPERATOR_M "<<-,&&,||,;;,<<,>>,<&,>&,<>,>|"
# define RESERVED "if,then,else,elif,fi,done,do,case,esac,while,until,for,in,!!"
/*# define SUBSTITUTE "$((,$(,)),),`"*/
# define SUBSTITUTE "$(,),`"

//# define DEFAULT_PROMPT "$user @ $host in $path [ $last_exit ]\n~> "

# define DEFAULT_PROMPT "%s%s%s @ %s%s in %s%s%s%s [ %s ]\n%s~>%s "

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

typedef enum e_prompt
{
	PROMPT_MAIN,
	PROMPT_HEREDOC,
	PROMPT_QUOTE,
	PROMPT_SUBSHELL
}	t_prompt;

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

typedef struct s_cmd
{
	char				**args;
	t_redirect_type		redirect_type;
	int					io[2];
}						t_cmd;

typedef struct s_btree
{
	void			*content;
	struct s_btree	*left;
	struct s_btree	*right;
}	t_btree;

typedef struct s_leaf
{
	t_node_type		type;
	t_cmd			*cmd;
}	t_leaf;

typedef struct s_expand
{
	char	*find;
	char	*mem;
	int		size;
	char	*envname;
	char	*envvar;
	char	*envvarr;
	int		offset;
}			t_expand;

int		ft_strcmp(const char *s1, const char *s2);

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
void	ft_lstclear_pipes(void *content);
void	ft_lstprint_pipes(t_list *lst, const char *s);

int		ft_handle_heredocs(t_list **lst);
char	*ft_read_heredoc(char *delimiter);

t_list	*ft_lex(const char *cmd_line);
t_list	*ft_doom_split(const char *input);
t_list	*ft_remove_whitespace(t_list *lst);
t_token	*ft_remove_quote(t_token *token);
t_token	*ft_expand(t_token *token);
t_list	*ft_fuse_word(t_list *lst);
t_btree	*ft_parse(t_list *tokens);
int		ft_exec(t_btree *root, char **env);

// tree related functions
void	ft_print_tree(t_btree *root, int level, int is_last);
t_btree	*ft_btree_new(void *content);
void	ft_btree_insert(t_btree **root, t_btree *ne,
			int (*cmp)(void *, void *));
void	ft_btree_insert_in(t_btree **root, t_btree *ne,
			int (*cmp)(void *, void *));
void	ft_btree_inorder(t_btree *root, void (*f)(void *));
void	ft_btree_preorder(t_btree *root, void (*f)(void *));
void	ft_btree_postorder(t_btree *root, void (*f)(void *));
int		ft_btree_size(t_btree *root);
int		ft_btree_height(t_btree *root);
void	ft_btree_clear(t_btree **root, void (*del)(void *));
void	ft_fill_tree(t_btree **root, t_list *pipes);

char	*ft_strjoin_free(const char *s1, const char *s2, t_joinfree flag);

t_leaf	*ft_create_leaf(t_node_type type, char	**args);
int		ft_cmp_leaf(void *s1, void *s2);
void	ft_free_leaf(void *leaf);

char	*ft_handle_multiline_quote(char *input);

bool	ft_findsubshell(t_list **tokens);
char	*ft_read_subshell(int level);

t_list	*ft_string_to_token(t_list *tokens, t_list *pre_tokens);

char	*ft_getenv(char *name);
char	*ft_readline(t_prompt id);

bool	ft_is_pipe(t_token *token);
bool	ft_is_logical(t_token *token);

char	*ft_gethostname(void);
char	*get_prompt_main(void);
#endif
