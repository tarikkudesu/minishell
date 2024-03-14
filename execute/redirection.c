/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:10:57 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/13 11:29:00 by ooulcaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	input_red(char *file, int input)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_throw("ERROR_OPEN_REDIRECTION_PROCESS", 1);
	if (dup2(fd, input) < 0)
		ft_throw("ERROR_DUP2_REDIRECTION_PROCESS", 1);
	if (-1 == close(fd))
		ft_throw("ERROR_CLOSE_REDIRECTION_PROCESS", 1);
}

static void	output_red(char *file, int output)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		ft_throw("ERROR_OPEN_REDIRECTION_PROCESS", 1);
	if (dup2(fd, output) < 0)
		ft_throw("ERROR_DUP2_REDIRECTION_PROCESS", 1);
	if (-1 == close(fd))
		ft_throw("ERROR_CLOSE_REDIRECTION_PROCESS", 1);
}

static void	append_red(char *file, int output)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		ft_throw("ERROR_OPEN_REDIRECTION_PROCESS", 1);
	if (dup2(fd, output) < 0)
		ft_throw("ERROR_DUP2_REDIRECTION_PROCESS", 1);
	if (-1 == close(fd))
		ft_throw("ERROR_CLOSE_REDIRECTION_PROCESS", 1);
}

static	void	herdoc_red(char *eof, int input)
{
	int	fd;

	fd = heredoc(eof);
	if (dup2(fd, input) < 0)
		ft_throw("ERROR_DUP2_REDIRECTION_PROCESS", 1);
	if (close(fd) < 0)
		ft_throw("ERROR_CLOSE_REDIRECTION_PROCESS", 1);
}

void	red_process(t_tokens *token, int input, int output, int *nbr)
{
	while (token && token->class != PIPE)
	{
		if (token->class == APPEND && token->stat == GENERAL)
			(append_red(token->right->string, output),
				token = token->right);
		else if (token->class == OUT_RED)
		{
			token = token->right;
			output_red(token->string, output);
		}
		else if (token->class == IN_RED)
		{
			token = token->right;
			input_red(token->string, input);
		}
		else if (token->class == HEREDOC)
		{
			token = token->right;
			herdoc_red(token->string, input);
		}
		else// if (token->class == WORD || token->class == ENV)
			(*nbr)++;
		token = token->right;
	}
}
