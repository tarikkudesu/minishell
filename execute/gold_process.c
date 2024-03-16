/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gold_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:15:56 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/16 15:38:14 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dup_in_out(int input, int output)
{
	if (input != STDIN_FILENO && dup2(input, STDIN_FILENO) < 0)
		ft_throw(strerror(errno), 1);
	if (output != STDOUT_FILENO && dup2(output, STDOUT_FILENO) < 0)
		ft_throw(strerror(errno), 1);
}

static	int	get_args_nbr(t_tokens *token)
{
	int		i;

	i = 0;
	while (token)
	{
		if (token->class == WORD)
			i++;
		token = token->right;
	}
	return (i);
}

static	char	**get_args(t_tokens *token)
{
	char	**args;
	int		i;

	args = malloc(sizeof(char *) * (get_args_nbr(token) + 1));
	if (!args)
		return (free_2d_char(args), \
		ft_putendl_fd("ERROR_MALLOC_GET_ARGS", 2), NULL);
	i = 0;
	while (token)
	{
		if (token->class == WORD)
		{
			args[i] = ft_strdup(token->string);
			if (!args[i])
				return (free_2d_char(args), \
				ft_putendl_fd("ERROR_MALLOC_GET_ARGS", 2), NULL);
			i++;
		}
		token = token->right;
	}
	args[i] = NULL;
	return (args);
}

static	void	ft_execve(t_shell *data, char **cmd_arg)
{
	char	*abs_path;
	// atexit(check);
	abs_path = absolute_path(cmd_arg[0], data->env);
	execve(abs_path, cmd_arg, data->env);
	free_2d_char(cmd_arg);
	ft_throw(strerror(errno), 127);
}

void	process(t_shell *data, t_tokens *token, int input, int output)
{
	char	**cmd_arg;

	if (red_process(token, input, output) < 0)
	{
		data->status = 1;
		if (data->number_of_commands > 1)
			exit(1);
		return ;
	}
	cmd_arg = get_args(token);
	dup_in_out(input, output);
	if (is_builtin(cmd_arg[0]))
		exec_builtin(data, cmd_arg);
	else
		ft_execve(data, cmd_arg);
}
