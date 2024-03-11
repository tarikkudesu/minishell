/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:24:04 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/10 23:04:48 by ooulcaid         ###   ########.fr       */
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
		ft_throw("ERROR_GET_PATH_PATH_PROCESSING", 1);
	tmp_char = ft_strjoin("/", cmd);
	if (!tmp_char)
		ft_throw("ERROR_JOIN_CMD_/", 1);
	i = -1;
	while (path[++i])
	{
		try = ft_strjoin(path[i], tmp_char);
		if (!try)
			ft_throw("ERROR_JOIN_CMD_ABSOLUTE", 1);
		if (!access(try, F_OK) && !access(try, X_OK))
			return (try);
		(free(try), try = NULL);
	}
	return (ft_throw("minishell: command not found", 127), NULL);
}
