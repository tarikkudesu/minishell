/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gold_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:15:56 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/20 21:20:55 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dup_in_out(int input, int output)
{
	if (input != STDIN_FILENO && dup2(input, STDIN_FILENO) < 0)
		ft_throw(ERR_DUP2, 1);
	if (input != STDIN_FILENO)
		close(input);
	if (output != STDOUT_FILENO && dup2(output, STDOUT_FILENO) < 0)
		ft_throw(ERR_DUP2, 1);
	if (output != STDOUT_FILENO)
		close(output);
}

static	int	get_args_nbr(t_tokens *token)
{
	int		i;

	i = 0;
	while (token)
	{
		if (token->class == WORD || token->class == ENV)
			i++;
		token = token->right;
	}
	return (i);
}

char	**get_args(t_tokens *token)
{
	char	**args;
	int		i;

	args = malloc(sizeof(char *) * (get_args_nbr(token) + 1));
	if (!args)
		return (free_2d_char(args), ft_putendl_fd(ERR_MAL, 2), NULL);
	i = 0;
	while (token)
	{
		if (token->class == WORD || token->class == ENV)
		{
			args[i] = ft_strdup(token->string);
			if (!args[i])
				return (free_2d_char(args), ft_putendl_fd(ERR_MAL, 2), NULL);
			i++;
		}
		token = token->right;
	}
	args[i] = NULL;
	return (args);
}

void	ft_execve(t_shell *data, char **cmd_arg)
{
	char	**env;
	char	*abs_path;

	env = env_to_array(data->env_list);
	abs_path = absolute_path(cmd_arg[0], env);
	execve(abs_path, cmd_arg, env);
	(free_2d_char(env), free_2d_char(cmd_arg));
	ft_throw(ERR_EXECVE, 127);
}

void	process(t_shell *data, t_tokens *token, int input, int output)
{
	char	**cmd_arg;

	if (red_process(data, token, input, output) == -1)
		exit(1);
	dup_in_out(input, output);
	cmd_arg = get_args(token);
	if (is_builtin(cmd_arg[0]))
		exec_builtin(data, cmd_arg);
	else
		ft_execve(data, cmd_arg);
}
