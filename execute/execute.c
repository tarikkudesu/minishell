/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 23:32:32 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/25 12:46:37 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	first_process(t_shell *data, t_tokens *token)
{
	int	pid;

	data->pipes[0] = malloc(sizeof(int) * 2);
	if (!data->pipes[0])
		ft_throw(ERR_MAL, 1);
	if (pipe(data->pipes[0]) < 0)
		ft_throw(ERR_PIPE, 1);
	pid = fork();
	if (pid < 0)
		ft_throw(ERR_FORK, 1);
	if (!pid)
	{
		(close(data->pipes[0][0]), \
		process(data, token, STDIN_FILENO, data->pipes[0][1]));
	}
	else
		close(data->pipes[0][1]);
}

static	void	last_process(t_shell *data, t_tokens *token)
{
	int	i;
	int	pid;

	i = data->cmd_nbr;
	pid = fork();
	if (pid < 0)
		ft_throw(ERR_MAL, 1);
	if (!pid)
	{
		(process(data, token,
				data->pipes[i - 2][0], STDOUT_FILENO));
	}
	else
	{
		close(data->pipes[i - 2][0]);
		waitpid(pid, &data->status, 0);
		if (WIFEXITED(data->status))
			data->status = WEXITSTATUS(data->status);
		else if (WIFSIGNALED(data->status))
			data->status = WTERMSIG(data->status) + 128;
	}
}

static	void	middle_process(t_shell *data, t_tokens *token)
{
	int	i;
	int	pid;

	i = 0;
	while (++i < data->cmd_nbr - 1)
	{
		data->pipes[i] = malloc(sizeof(int) * 2);
		if (!data->pipes[i])
			ft_throw(ERR_MAL, 1);
		if (pipe(data->pipes[i]) < 0)
			ft_throw(ERR_PIPE, 1);
		pid = fork();
		if (pid < 0)
			ft_throw(ERR_FORK, 1);
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
	signal(SIGINT, ctl_c);
	if (data->cmd_nbr == 1)
		single_cmd(data);
	else
	{
		data->pipes = malloc(sizeof(int *) *(data->cmd_nbr - 1));
		if (!data->pipes)
			ft_throw(ERR_MAL, 1);
		first_process(data, data->tree);
		middle_process(data, data->tree->left);
		while (wait(NULL) >= 0)
			;
	}
	if (data->doc_fd != -1)
	{
		close(data->doc_fd);
		data->doc_fd = -1;
	}
}
