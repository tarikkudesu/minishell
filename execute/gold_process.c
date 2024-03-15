/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gold_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:15:56 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/14 21:57:52 by ooulcaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	char	**get_args(t_tokens *token, int nbr_arg)
{
	char	**args;
	int		i;

	i = 0;
	args = malloc(sizeof(char *) * (nbr_arg + 1));
	if (!args)
		ft_throw("ERROR_MALLOC_GET_ARGS", 1);
	while (i < nbr_arg)
	{
		if (token->class == WORD || token->class == ENV)
		{
			args[i] = ft_strdup(token->string);
			if (!args[i++])
				ft_throw("ERROR_STRDUP_GET_ARGS", 1);
			token = token->right;
		}
		else if (token->class != PIPE)
			token = token->right;
	}
	args[i] = NULL;
	return (args);
}

static	void	ft_execve(t_shell *data, char **cmd_arg, int input, int output)
{
	char	*abs_path;

	abs_path = absolute_path(cmd_arg[0], data->env);
	if (input != STDIN_FILENO && dup2(input, STDIN_FILENO))
		ft_throw(strerror(errno), 1);
	if (output != STDOUT_FILENO && dup2(output, STDOUT_FILENO) < 0)
		ft_throw(strerror(errno), 1);
	execve(abs_path, cmd_arg, data->env);
	free_2d_char(cmd_arg);
	ft_throw(strerror(errno), 128);
}

void	process(t_shell *data, t_tokens *token, int input, int output)
{
	char		**cmd_arg;
	int			nbr_arg;

	nbr_arg = 0;
	if (red_process(token, input, output, &nbr_arg) < 0)
	{
		data->status = 1;
		return ;
	}
	cmd_arg = get_args(token, nbr_arg);
	if (is_builtin(cmd_arg[0]))
		exec_builtin(data, cmd_arg);
	else
		ft_execve(data, cmd_arg, input, output);
}
