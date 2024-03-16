/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 23:32:32 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/16 15:09:12 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	first_process(t_shell *data, t_tokens *token)
{
	int	pid;

	if (data->number_of_commands > 1)
	{
		data->pipes[0] = malloc(sizeof(int) * 2);
		if (!data->pipes[0])
			ft_throw("ERROR_MALLOC_PIPE_EXECUTE", 1);
		if (pipe(data->pipes[0]) < 0)
			ft_throw("ERROR_CREAT_PIPE_EXECUTE", 1);
	}
	pid = fork();
	if (pid < 0)
		ft_throw("ERROR_FORK_MIDDLE_COMMAND", 1);
	if (!pid)
	{
		if (data->number_of_commands > 1)
			(close(data->pipes[0][0]),
				process(data, token, STDIN_FILENO, data->pipes[0][1]));
		else
			process(data, token, STDIN_FILENO, STDOUT_FILENO);
	}
	else if (pid && data->number_of_commands > 1)
		close(data->pipes[0][1]);
}

static	void	last_process(t_shell *data, t_tokens *token)
{
	int	i;
	int	pid;

	i = data->number_of_commands;
	pid = fork();
	if (pid < 0)
		ft_throw("ERROR_FORK_LAST_COMMAND", 1);
	if (!pid)
		(process(data, token,
				data->pipes[i - 2][0], STDOUT_FILENO));
	else
		close(data->pipes[i - 2][0]);
}

static	void	middle_process(t_shell *data, t_tokens *token)
{
	int	i;
	int	pid;

	i = 0;
	while (++i < data->number_of_commands - 1)
	{
		data->pipes[i] = malloc(sizeof(int) * 2);
		if (!data->pipes[i])
			ft_throw("ERROR_MALLOC_PIPE_EXECUTE", 1);
		if (pipe(data->pipes[i]) < 0)
			ft_throw("ERROR_CREAT_PIPE_EXECUTE", 1);
		pid = fork();
		if (pid < 0)
			ft_throw("ERROR_FORK_MIDDLE_COMMAND", 1);
		if (!pid)
		{
			close(data->pipes[i][0]);
			process(data, token, data->pipes[i - 1][0], data->pipes[i][1]);
		}
		else
			(close(data->pipes[i][1]), close(data->pipes[i - 1][0]),
				token = token->left);
	}
	last_process(data, token);
}

static	int	parent_built_in(t_shell *data)
{
	int	fd_in;
	int	fd_out;

	fd_in = dup(STDIN_FILENO);
	if (fd_in < 0)
		return (throw_error("ERROR_DUP_PARENT_BUILTIN"));
	fd_out = dup(STDOUT_FILENO);
	if (fd_out < 0)
		return (close(fd_in), throw_error("ERROR_DUP_PARENT_BUILTIN"));
	process(data, data->tree, STDIN_FILENO, STDOUT_FILENO);
	if (dup2(fd_in, STDIN_FILENO) < 0 || dup2(fd_out, STDOUT_FILENO) < 0)
		ft_throw("ERROR_LOST_STDIN_AND_STDOUT", 1);
	close(fd_in);
	close(fd_out);
	return (0);
}

void	execute(t_shell *data)
{
	if (data->number_of_commands == 1 && is_builtin(data->tree->string))
		parent_built_in(data);
	else
	{
		if (data->number_of_commands == 1)
			first_process(data, data->tree);
		else
		{
			data->pipes = malloc(sizeof(int *)
					*(data->number_of_commands - 1));
			if (!data->pipes)
				ft_throw("ERROR_MALLOC_PIPES_EXECUTE", 1);
			first_process(data, data->tree);
			middle_process(data, data->tree->left);
		}
		while (waitpid(-1, &data->status, 0) >= 0)
		{
			if (WIFSIGNALED(data->status))
				data->status = WTERMSIG(data->status) + 128;
			else if (WIFEXITED(data->status))
				data->status = WEXITSTATUS(data->status);
		}
	}
}
