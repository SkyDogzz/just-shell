#include "../../includes/minishell.h"

bool	ft_is_pipe(t_token *token)
{
	return (ft_strlen(token->content) == 1 && token->token_type == T_OPERATOR
		&& ft_strncmp(token->content, "|", 1) == 0);
}
