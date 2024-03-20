/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:44:38 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/20 14:32:05 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	minishell(t_shell *data)
{
	if (check_quoting(data->line))
		return (ft_putendl_fd(ERR_UNCLOSED_QUOTES, 2));
	if (lexer(data))
		return ;
	fonction_mli7a(data);
	// if (pars(data))
	// 	return ;
	// if (syntax(data))
	// 	return ;
	// command_tree(data);
	// execute(data);
	// if (data->cmd_nbr > 1)
	// 	(free_2d_int(data->pipes, data->cmd_nbr - 1), \
	// 	data->pipes = NULL);
}

void	read_line(t_shell *data)
{
	char	*line;

	while (1)
	{
		rl_initialize();
		line = readline("\033[1;32m➜  \033[1;36mminishell \033[0m");
		if (!line)
			return ;
		if (*line)
		{
			add_history(line);
			data->line = line;
			data->stat = GENERAL;
			minishell(data);
			(clear_command_tree(&data->tokens), data->tokens = NULL);
			(clear_command_tree(&data->tree), data->tree = NULL);
		}
		free(line);
		line = NULL;
		data->line = NULL;
	}
}
