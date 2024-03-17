/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:40:57 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/17 17:10:29 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	parent_built_in(t_shell *data, char **args)
{
	int	fd_in;
	int	fd_out;

	fd_in = dup(STDIN_FILENO);
	if (fd_in < 0)
		return (throw_error("ERROR_DUP_PARENT_BUILTIN"));
	fd_out = dup(STDOUT_FILENO);
	if (fd_out < 0)
		return (close(fd_in), throw_error("ERROR_DUP_PARENT_BUILTIN"));
	if (!red_process(data, data->tree, STDIN_FILENO, STDOUT_FILENO))
		exec_builtin(data, args);
	else
		data->status = 1;
	if (dup2(fd_in, STDIN_FILENO) < 0 || dup2(fd_out, STDOUT_FILENO) < 0)
		ft_throw("ERROR_LOST_STDIN_AND_STDOUT", 1);
	close(fd_in);
	close(fd_out);
	return (0);
}

void	single_cmd(t_shell *data)
{
	char	**args;
	int		pid;

	args = get_args(data->tree);
	if (!args || !*args)
		return ;
	if (is_builtin(*args))
		parent_built_in(data, args);
	else
	{
		pid = fork();
		if (pid < 0)
			ft_throw("ERROR_FORK", 1);
		if (!pid)
		{
			if (red_process(data, data->tree, STDIN_FILENO, STDOUT_FILENO) < 0)
				exit(1);
			ft_execve(data, args);
		}
		else
		{
			wait(&data->status);
			if (WIFEXITED(data->status))
				data->status = WEXITSTATUS(data->status);
			else if (WIFSIGNALED(data->status))
				data->status = WTERMSIG(data->status) + 128;
		}
	}
}
