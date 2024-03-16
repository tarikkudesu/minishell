/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:24:04 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/16 17:50:59 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_existance(char *file)
{
	struct	stat	st;

	stat(file, &st);
	if (S_ISDIR(st.st_mode))
		ft_throw(" is a directory", 126);
	else if (access(file, F_OK))
		ft_throw(" No such file or directory", 127);
	else if (access(file, X_OK))
		ft_throw(" Permission denied", 126);
	return (1);
}

char	**get_path(char **env)
{
	int		i;
	char	**splited;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PATH", 4))
		{
			splited = ft_split(env[i] + 5, ':');
			if (!splited)
				ft_throw("ERROR_SPLIT_GET_PATH", 1);
			return (splited);
		}
	}
	return (NULL);
}

char	*absolute_path(char	*cmd, char **env)
{
	char	**path;
	char	*try;
	char	*tmp_char;
	int		i;

	if ((cmd[0] == '.' || cmd[0] == '/') && check_existance(cmd))
		return (cmd);
	path = get_path(env);
	if (!path)
		ft_throw("minishell: command not found", 127);
	tmp_char = ft_strjoin("/", cmd);
	if (!tmp_char)
		(free_2d_char(path), ft_throw("ERROR_JOIN_CMD_/", 1));
	i = -1;
	while (path[++i])
	{
		try = ft_strjoin(path[i], tmp_char);
		if (!try)
			(free_2d_char(path), free(tmp_char), \
			ft_throw("ERROR_JOIN_CMD_ABSOLUTE", 1));
		if (!access(try, F_OK) && !access(try, X_OK))
			return (free(tmp_char), try);
		(free(try), try = NULL);
	}
	return (ft_throw(" command not found", 127), NULL);
}
