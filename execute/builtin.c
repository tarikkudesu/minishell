/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:36:29 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/20 16:30:23 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *string)
{
	if (!ft_strcmp(string, "echo")
		|| !ft_strcmp(string, "cd")
		|| !ft_strcmp(string, "exit")
		|| !ft_strcmp(string, "export")
		|| !ft_strcmp(string, "unset")
		|| !ft_strcmp(string, "pwd")
		|| !ft_strcmp(string, "env"))
		return (1);
	return (0);
}

void	exec_builtin(t_shell *data, char **cmd_arg)
{
	if (!ft_strcmp(cmd_arg[0], "echo"))
		ft_echo(data, cmd_arg + 1);
	else if (!ft_strcmp(cmd_arg[0], "cd") && cmd_arg[1])
		ft_cd(data, cmd_arg[1]);
	else if (!ft_strcmp(cmd_arg[0], "cd"))
		ft_cd(data, NULL);
	else if (!ft_strcmp(cmd_arg[0], "pwd"))
		ft_pwd(data);
	else if (!ft_strcmp(cmd_arg[0], "env"))
		ft_env(data, data->env_list);
	else if (!ft_strcmp(cmd_arg[0], "unset"))
		ft_unset(data, &data->env_list, cmd_arg + 1);
	else if (!ft_strcmp(cmd_arg[0], "export") && cmd_arg[1])
		ft_export(data, &data->env_list, cmd_arg + 1, 1);
	else if (!ft_strcmp(cmd_arg[0], "export"))
		ft_export(data, &data->env_list, NULL, 0);
	else if (!ft_strcmp(cmd_arg[0], "exit"))
		ft_exit(data, cmd_arg);
	free_2d_char(cmd_arg);
}
