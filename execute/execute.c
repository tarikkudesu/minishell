/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 23:32:32 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/14 23:52:11 by ooulcaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	first_process(t_shell *data, t_tokens *token)
{
	if (data->number_of_commands > 1)
	{
		data->pipes[0] = malloc(sizeof(int) * 2);
		if (!data->pipes[0])
			ft_throw("ERROR_MALLOC_PIPE_EXECUTE", 1);
		if (pipe(data->pipes[0]) < 0)
			ft_throw("ERROR_CREAT_PIPE_EXECUTE", 1);
	}
	data->pids[0] = fork();
	if (data->pids[0] < 0)
		ft_throw("ERROR_FORK_MIDDLE_COMMAND", 1);
	if (!data->pids[0])
	{
		if (data->number_of_commands > 1)
			(close(data->pipes[0][0]),
				process(data, token, STDIN_FILENO, data->pipes[0][1]));
		else
			process(data, token, STDIN_FILENO, STDOUT_FILENO);
	}
	else if (data->pids[0] && data->number_of_commands > 1)
		close(data->pipes[0][1]);
}

void	last_process(t_shell *data, t_tokens *token)
{
	int	i;

	i = data->number_of_commands;
	data->pids[i - 1] = fork();
	if (data->pids[i - 1] < 0)
		ft_throw("ERROR_FORK_LAST_COMMAND", 1);
	if (!data->pids[i - 1])
		(process(data, token,
				data->pipes[i - 2][0], STDOUT_FILENO));
	else
		close(data->pipes[i - 2][0]);
}

void	middle_process(t_shell *data, t_tokens *token)
{
	int	i;

	i = 0;
	while (++i < data->number_of_commands - 1)
	{
		data->pipes[i] = malloc(sizeof(int) * 2);
		if (!data->pipes[i])
			ft_throw("ERROR_MALLOC_PIPE_EXECUTE", 1);
		if (pipe(data->pipes[i]) < 0)
			ft_throw("ERROR_CREAT_PIPE_EXECUTE", 1);
		data->pids[i] = fork();
		if (data->pids[i] < 0)
			ft_throw("ERROR_FORK_MIDDLE_COMMAND", 1);
		if (!data->pids[i])
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

void	parent_built_in(t_shell *data)
{
	int	fd_in;
	int	fd_out;

	fd_in = open("/Users/ooulcaid/.in", O_CREAT | O_RDWR, 0777);
	fd_out = open("/Users/ooulcaid/.out", O_CREAT | O_RDWR, 0777);
	if (fd_in < 0 | fd_out < 0)
		ft_throw("ERROR_OPEN_PARENT_BUILTIN", 1);
	if (unlink("/Users/ooulcaid/.in") < 0
		|| unlink("/Users/ooulcaid/.out") < 0)
		ft_throw("ERROR_UNLINK_PARENT_BUILTIN", 1);
	if (dup2(STDIN_FILENO, fd_in) < 0 || dup2(STDOUT_FILENO, fd_out) < 0)
		ft_throw("ERROR_DUP2_PARENT_BUILTIN", 1);
	process(data, data->tree, STDIN_FILENO, STDOUT_FILENO);
	if (dup2(fd_in, STDIN_FILENO) < 0 || dup2(fd_out, STDOUT_FILENO) < 0)
		ft_throw("ERROR_DUP2_PARENT_BUILTIN", 1);
}

void	execute(t_shell *data)
{
	int			status;

	if (data->number_of_commands == 1 && is_builtin(data->tree->string))
		parent_built_in(data);
	else
	{
		data->pids = malloc(sizeof(int) * data->number_of_commands);
		if (!data->pids)
			ft_throw("ERROR_MALLOC_PIDS_EXECUTE", 1);
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
		while (waitpid(-1, &status, 0) >= 0)
			((WIFSIGNALED(status) && (data->status = WTERMSIG(status) + 128)),
				WIFEXITED(status)
				&& (data->status = WEXITSTATUS(status)));
	}
}
