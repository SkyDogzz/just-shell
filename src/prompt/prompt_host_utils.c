/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_host_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 21:41:30 by yandry            #+#    #+#             */
/*   Updated: 2025/04/20 22:29:19 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_env.h"
#include "ft_prompt.h"

static int	get_trimmed_format_len(bool is_root)
{
	char	*trimmed_format;
	int		len;

	if (is_root)
		trimmed_format = ft_strtrim(HOST_ROOT, "%s");
	else
		trimmed_format = ft_strtrim(HOST_REGULAR, "%s");
	len = ft_strlen(trimmed_format);
	free(trimmed_format);
	return (len);
}

static char	*get_formatted_host(char *host, bool is_root)
{
	char	**splitted_host;
	char	*hostname;
	char	*formatted_host;
	int		len;

	splitted_host = ft_split(host, '.');
	if (!splitted_host)
		return (NULL);
	hostname = ft_strdup(splitted_host[0]);
	ft_free_array((void ***)&splitted_host);
	if (!hostname)
		return (NULL);
	len = ft_strlen(hostname) + get_trimmed_format_len(is_root) + 1;
	formatted_host = ft_calloc(len, sizeof(char));
	if (!formatted_host)
		return (free(hostname), NULL);
	if (is_root)
		ft_snprintf(formatted_host, len, HOST_ROOT, hostname);
	else
		ft_snprintf(formatted_host, len, HOST_REGULAR, hostname);
	free(hostname);
	return (formatted_host);
}

const char	*get_prompt_host(t_list *env)
{
	t_env		*host_env;
	const char	*user;
	char		*host;
	char		*hostname;

	host_env = ft_get_env(env, "HOSTNAME");
	user = get_prompt_user(env);
	if (!host_env)
		hostname = ft_strdup("nowhere");
	else
		hostname = ft_strdup(host_env->value);
	host = get_formatted_host(hostname, ft_strncmp(user, "root", 4) == 0);
	return (host);
}
