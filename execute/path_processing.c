/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:24:04 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/08 12:13:27 by ooulcaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_path(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->environ, "PATH", 4))
			return (ft_split(tmp->environ + 5, ':'));
		tmp = tmp->next; 
	}
}

char	*absolute_path(t_env *env, char *cmd)
{
	t_env	*tmp;
	char	**path;
	char	*try;
	char	*tmp_char;
	int		i;

	if (*cmd == '.' || *cmd == '/')
		return (cmd);
	i = -1;
	path = get_path(env);
	if (!path)
		ft_throw("ERROR_GET_PATH_PATHPROCESSING");
	tmp_char = ft_strjoin(cmd, "/");
	if (!tmp_char)
		ft_throw("ERROR_JOIN_CMD_/"); // free(path in this failure)
	while (path[++i])
	{
		try = ft_strjoin(path[i], tmp_char);
		if (!tmp_char)
			ft_throw("ERROR_JOIN_CMD_/"); // free(path in this failure)
	}
}