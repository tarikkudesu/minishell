/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:10:05 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/23 18:36:37 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_if(int processes, int status)
{
	if (processes > 1)
		exit (status);
}

void	new_old_pwd(t_shell *data)
{
	t_env	*node;
	char	*name;
	char	*value;

	name = ft_strdup("OLDPWD");
	value = ft_strdup(data->pwd);
	if (!name || !value)
		return (ft_putendl_fd(ERR_MAL, 2));
	node = env_new(name, value);
	if (!node)
		return (free(name), free(value), ft_putendl_fd(ERR_MAL, 2));
	env_add_back(&data->env_list, node);
}

void	update_pwd(t_shell *data, t_env **tmp)
{
	char	*value;

	value = ft_strdup(data->pwd);
	if (!value)
		return (ft_putendl_fd(ERR_MAL, 2));
	free((*tmp)->value);
	(*tmp)->value = value;
}

void	update(t_shell *data)
{
	t_env	*tmp;

	tmp = data->env_list;
	while (tmp && ft_strcmp(tmp->name, "OLDPWD"))
		tmp = tmp->next;
	if (!tmp)
		new_old_pwd(data);
	else if (!ft_strcmp(tmp->name, "OLDPWD"))
		update_pwd(data, &tmp);
	(free(data->pwd), data->pwd = getcwd(NULL, 0));
	tmp = data->env_list;
	while (tmp && ft_strcmp(tmp->name, "PWD"))
		tmp = tmp->next;
	if (tmp)
		update_pwd(data, &tmp);
}

void	ft_cd(t_shell *data, char *path)
{
	struct stat	st;

	if (!path || !ft_strcmp(path, "~"))
	{
		if (chdir("/Users/tamehri") < 0)
			return (perror(ERR), data->status = 1, exit_if(data->cmd_nbr, 1));
	}
	else if (stat(path, &st) < 0)
		return (perror(ERR), data->status = 1, exit_if(data->cmd_nbr, 1));
	else if (!S_ISDIR(st.st_mode))
	{
		(ft_putstr_fd(ERR, 2), ft_putstr_fd(path, 2), \
			ft_putendl_fd(" Not a directory", 2), data->status = 1);
		return (exit_if(data->cmd_nbr, 1));
	}
	else if (chdir(path) < 0)
		return (data->status = 1, \
		ft_putendl_fd("minishell error : could not change directory", 2));
	data->status = 0;
	update(data);
	return (exit_if(data->cmd_nbr, 0));
}
