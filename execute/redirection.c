/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:10:57 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/20 17:10:49 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	input_red(char *file, int input)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror(ERR_OPEN), -1);
	if (dup2(fd, input) < 0)
		return (perror(ERR_DUP2), -1);
	close(fd);
	return (0);
}

static int	output_red(char *file, int output)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror(ERR_OPEN), -1);
	if (dup2(fd, output) < 0)
		return (perror(ERR_DUP2), -1);
	close(fd);
	return (0);
}

static int	append_red(char *file, int output)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (perror(ERR_OPEN), -1);
	if (dup2(fd, output) < 0)
		return (perror(ERR_DUP2), -1);
	close(fd);
	return (0);
}

static	int	herdoc_red(t_shell *data, int input)
{
	if (data->doc_fd != -1 && dup2(data->doc_fd, input) < 0)
		return (perror(ERR_DUP2), -1);
	close(data->doc_fd);
	data->doc_fd = -1;
	return (0);
}

int	red_process(t_shell *data, t_tokens *token, int input, int output)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->class == APPEND)
			i = append_red(token->right->string, output);
		else if (token->class == OUT_RED)
			i = output_red(token->right->string, output);
		else if (token->class == IN_RED)
			i = input_red(token->right->string, input);
		else if (token->class == HEREDOC)
			i = herdoc_red(data, input);
		token = token->right;
		if (i < 0)
			return (-1);
	}
	return (0);
}
