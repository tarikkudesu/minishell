/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:36:29 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/14 13:17:25 by tamehri          ###   ########.fr       */
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
		ft_echo(cmd_arg + 1);
	else if (!ft_strcmp(cmd_arg[0], "cd") && cmd_arg[1])
		ft_cd(cmd_arg[1]);
	else if (!ft_strcmp(cmd_arg[0], "cd"))
		ft_cd(NULL);
	else if (!ft_strcmp(cmd_arg[0], "pwd"))
		ft_pwd(data);
	else if (!ft_strcmp(cmd_arg[0], "env"))
		ft_env(data->env_list);
	else if (!ft_strcmp(cmd_arg[0], "unset"))
		ft_unset(&data->env_list, cmd_arg + 1);
	else if (!ft_strcmp(cmd_arg[0], "export") && cmd_arg[1])
		ft_export(&data->env_list, cmd_arg + 1, 1);
	else if (!ft_strcmp(cmd_arg[0], "export"))
		ft_export(&data->env_list, NULL, 0);
	else if (!ft_strcmp(cmd_arg[0], "exit"))
		ft_exit(cmd_arg);
	free_2d_char(cmd_arg);
}
