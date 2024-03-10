/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:24:04 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/10 10:17:00 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_path(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], "PATH", 4))
			return (ft_split(env[i] + 5, ':'));
	return (NULL);
}

char	*absolute_path(char	*cmd, char **env)
{
	char	**path;
	char	*try;
	char	*tmp_char;
	int		i;

	if (*cmd == '.' || *cmd == '/')
		return (cmd);
	path = get_path(env);
	if (!path)
		ft_throw("ERROR_GET_PATH_PATH_PROCESSING");
	tmp_char = ft_strjoin("/", cmd);
	if (!tmp_char)
		(ft_throw("ERROR_JOIN_CMD_/"));
	i = -1;
	while (path[++i])
	{
		try = ft_strjoin(path[i], tmp_char);
		if (!try)
			(ft_throw("ERROR_JOIN_CMD_ABSOLUTE"));
		if (!access(try, F_OK) && !access(try, X_OK))
			return (try);
		(free(try), try = NULL);
	}
	return (ft_throw("ERROR_GET_ABSPATH"), NULL);
}
