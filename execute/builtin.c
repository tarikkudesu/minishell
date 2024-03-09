/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:36:29 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/08 23:31:12 by ooulcaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(t_tokens *token)
{
	while (token && token->string != '|')
	{
		if (!ft_strcmp(token->string, "echo")
			|| !ft_strcmp(token->string, "cd")
			|| !ft_strcmp(token->string, "exit")
			|| !ft_strcmp(token->string, "export")
			|| !ft_strcmp(token->string, "unset")
			|| !ft_strcmp(token->string, "pwd")
			|| !ft_strcmp(token->string, "env"))
			return (1);
		if (token->class == WORD)
			return (0);
		if (token->right && token->right->string[0] != '|')
			token = token->right->right;
	}
	return (0);
}

void	exec_builtin(t_shell *data, char **cmd_arg, int input, int output)
{
	if (!ft_strcmp(cmd_arg[0], "echo"))
		ft_echo(cmd_arg + 1);
	else if (!ft_strcmp(cmd_arg[0], "cd") && cmd_arg[1])
		ft_cd(cmd_arg[1]);
	else if (!ft_strcmp(cmd_arg[0], "cd"))
		ft_cd(NULL);
	else if (!ft_strcmp(cmd_arg[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd_arg[0], "exit"))
		ft_exit();
	else if (!ft_strcmp(cmd_arg[0], "env"))
		ft_env(data->env_list);
	else if (!ft_strcmp(cmd_arg[0], "unset"))
		ft_unset(&(data->env_list), cmd_arg + 1);
	else if (!ft_strcmp(cmd_arg[0], "export") && cmd_arg[1])
		ft_export(&(data->env_list), cmd_arg + 1, 1);
	else if (!ft_strcmp(cmd_arg[0], "export"))
		ft_export((&data->env_list), NULL, 0);
}
