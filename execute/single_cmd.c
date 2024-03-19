/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:40:57 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/19 18:15:03 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	parent_built_in(t_shell *data, char **args)
{
	int	fd_in;
	int	fd_out;

	fd_in = dup(STDIN_FILENO);
	if (fd_in < 0)
		return (data->status = 1, perror(ERR_DUP));
	fd_out = dup(STDOUT_FILENO);
	if (fd_out < 0)
		return (close(fd_in), data->status = 1, perror(ERR_DUP));
	if (!red_process(data, data->tree, STDIN_FILENO, STDOUT_FILENO))
		exec_builtin(data, args);
	else
		data->status = 1;
	if (dup2(fd_in, STDIN_FILENO) < 0 || dup2(fd_out, STDOUT_FILENO) < 0)
		return (close(fd_in), close(fd_out), data->status = 1, \
		perror(ERR_DUP2));
	close(fd_in);
	close(fd_out);
}

void	single_cmd(t_shell *data)
{
	char	**args;
	int		pid;

	args = get_args(data->tree);
	if (!args || !*args)
		return ;
	if (is_builtin(*args))
		return (parent_built_in(data, args));
	pid = fork();
	if (pid < 0)
		ft_throw(ERR_FORK, 1);
	if (!pid)
	{
		if (red_process(data, data->tree, STDIN_FILENO, STDOUT_FILENO) < 0)
			exit(1);
		ft_execve(data, args);
	}
	waitpid(pid, &data->status, 0);
	if (WIFEXITED(data->status))
		data->status = WEXITSTATUS(data->status);
	else if (WIFSIGNALED(data->status))
		data->status = WTERMSIG(data->status) + 128;
	free_2d_char(args);
}
