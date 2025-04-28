/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skydogzz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 06:40:36 by skydogzz          #+#    #+#             */
/*   Updated: 2025/04/28 07:20:04 by skydogzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_history.h"

void	retreive_history(t_list *env)
{
	int		fd;
	char	*line;
	char	*path;
	char	*trimmed;

	path = ft_strreplace(HISTORY_FILE, "~", ft_get_env(env, "HOME")->value);
	if (!path)
		return ;
	fd = open(path, O_RDONLY);
	free(path);
	if (fd <= 0)
		return ;
	line = ft_get_next_line(fd);
	while (line)
	{
		if (ft_strcmp(line, "\n") != 0)
		{
			trimmed = ft_strtrim(line, "\n");
			add_history(trimmed);
			free(trimmed);
		}
		free(line);
		line = ft_get_next_line(fd);
	}
	close(fd);
}

void	store_history(char *input, t_list *env)
{
	char		*path;
	static int	fd = -1;

	add_history(input);
	path = ft_strreplace(HISTORY_FILE, "~", ft_get_env(env, "HOME")->value);
	if (!path)
		return ;
	if (fd == -1)
	{
		fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd < 0)
		{
			free(path);
			return ;
		}
	}
	if (write(fd, input, strlen(input)) < 0
		|| write(fd, "\n", 1) < 0)
		free(path);
}
