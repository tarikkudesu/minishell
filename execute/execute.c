/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 23:32:32 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/18 21:49:59 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	first_process(t_shell *data, t_tokens *token)
{
	int	pid;

	data->pipes[0] = malloc(sizeof(int) * 2);
	if (!data->pipes[0])
		ft_throw("ERROR_MALLOC_PIPE_EXECUTE", 1);
	if (pipe(data->pipes[0]) < 0)
		ft_throw("ERROR_CREAT_PIPE_EXECUTE", 1);
	pid = fork();
	if (pid < 0)
		ft_throw("ERROR_FORK_MIDDLE_COMMAND", 1);
	if (!pid)
		(close(data->pipes[0][0]), \
		process(data, token, STDIN_FILENO, data->pipes[0][1]));
	else
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

void	execute(t_shell *data)
{
	if (data->number_of_commands == 1)
		single_cmd(data);
	else
	{
		data->pipes = malloc(sizeof(int *) *(data->number_of_commands - 1));
		if (!data->pipes)
			ft_throw("ERROR_MALLOC_PIPES_EXECUTE", 1);
		first_process(data, data->tree);
		middle_process(data, data->tree->left);
		while (waitpid(-1, &data->status, 0) >= 0)
			;
		data->status = WEXITSTATUS(data->status);
		if (WIFSIGNALED(data->status))
			data->status = WTERMSIG(data->status) + 128;
		else if (WIFEXITED(data->status))
			data->status = WEXITSTATUS(data->status);
	}
}
