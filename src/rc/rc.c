/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:30:23 by tstephan          #+#    #+#             */
/*   Updated: 2025/07/04 17:37:12 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_rc(t_rc *rc)
{
	ft_lstclear(&rc->alias, del_alias);
	free(rc);
}

t_rc	*parse_rc(void)
{
	t_rc	*rc;
	int		fd;
	char	*line;

	fd = open(RC_FILE, O_RDONLY);
	if (fd < 0)
		return (NULL);
	rc = malloc(sizeof(t_rc));
	if (!rc)
		return (NULL);
	rc->alias = NULL;
	line = ft_get_next_line(fd);
	while (line)
	{
		rc->alias = parse_alias(rc->alias, line);
		free(line);
		line = ft_get_next_line(fd);
	}
	return (rc);
}
