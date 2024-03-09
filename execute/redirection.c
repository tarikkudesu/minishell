/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:10:57 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/09 20:31:51 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	input_red(char *file, int input)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_throw("ERROR_OPEN_REDIRECTION_PROCESS");
	if (dup2(fd, input) < 0)
		ft_throw("ERROR_DUP2_REDIRECTION_PROCESS");
	if (-1 == close(fd))
		ft_throw("ERROR_CLOSE_REDIRECTION_PROCESS");
}

static void	output_red(char *file, int output)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		ft_throw("ERROR_OPEN_REDIRECTION_PROCESS");
	if (dup2(fd, output) < 0)
		ft_throw("ERROR_DUP2_REDIRECTION_PROCESS");
	if (-1 == close(fd))
		ft_throw("ERROR_CLOSE_REDIRECTION_PROCESS");
}

static void	append_red(char *file, int output)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		ft_throw("ERROR_OPEN_REDIRECTION_PROCESS");
	if (dup2(fd, output) < 0)
		ft_throw("ERROR_DUP2_REDIRECTION_PROCESS");
	if (-1 == close(fd))
		ft_throw("ERROR_CLOSE_REDIRECTION_PROCESS");
}

static	void	herdoc_red(char *eof, int input)
{
	int	fd;

	fd = heredoc(eof);
	if (fd < 0)
		ft_throw("ERROR_HERDOC_REDIRECTION_PROCESS");
	if (dup2(fd, input) < 0)
		ft_throw("ERROR_DUP2_REDIRECTION_PROCESS");
	if (-1 == close(fd))
		ft_throw("ERROR_CLOSE_REDIRECTION_PROCESS");
}

void	red_process(t_tokens *token, int input, int output, int *nbr)
{
	while (token && token->class != PIPE)
	{
		if (token->class == APPEND)
			(append_red(token->right->string, output),
				token = token->right);
		else if (token->class == OUTPUT_RED)
		{
			token = token->right;
			output_red(token->string, output);
		}
		else if (token->class == INPUT_RED)
		{
			token = token->right;
			input_red(token->string, input);
		}
		else if (token->class == HEREDOC)
		{
			token = token->right;
			herdoc_red(token->string, input);
		}
		else if (token->class == WORD)
			(*nbr)++;
		token = token->right;
	}
}
