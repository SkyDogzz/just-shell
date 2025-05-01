/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skydogzz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 06:40:36 by skydogzz          #+#    #+#             */
/*   Updated: 2025/05/01 20:54:54 by skydogzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_history.h"

static char	*ft_strreplaceall(char *s, char f, char r)
{
	char	*start;

	start = s;
	while (*s++)
	{
		if (*s == f)
			*s = r;
	}
	return (start);
}

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
			add_history(ft_strreplaceall(trimmed, ';', '\n'));
			free(trimmed);
		}
		free(line);
		line = ft_get_next_line(fd);
	}
	close(fd);
}

void	ft_add_history(char *input, bool store, t_list *env)
{
	static char		*pending = NULL;
	static size_t	len = 0;
	char			*path;
	int				fd;
	size_t			in_len;
	char			*tmp;

	path = ft_strreplace(HISTORY_FILE, "~", ft_get_env(env, "HOME")->value);
	if (!path)
		return ;
	fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd < 0)
	{
		free(path);
		return ;
	}
	if (!input && store && pending)
	{
		add_history(pending);
		write(fd, ft_strreplaceall(pending, '\n', ';'), strlen(pending));
		write(fd, "\n\n", 2);
		free(pending);
		pending = NULL;
		len = 0;
		return ;
	}
	if (!input)
		return ;
	if (store)
	{
		if (pending)
		{
			add_history(pending);
			write(fd, pending, strlen(pending));
			free(pending);
			pending = NULL;
			len = 0;
		}
		add_history(input);
		write(fd, input, strlen(input));
		write(fd, "\n\n", 2);
	}
	else
	{
		in_len = strlen(input);
		tmp = realloc(pending, len + in_len + 1);
		if (!tmp)
			return ;
		pending = tmp;
		memcpy(pending + len, input, in_len);
		len += in_len;
		pending[len] = '\0';
	}
}
