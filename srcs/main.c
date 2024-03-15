/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:26:15 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/15 14:43:58 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	minishell(t_shell *data)
{
	if (lexer(data))
		return ;
	// if (pars(data))
		// return ;
	// if (check_syntax(data))
		// return ;
	// fonction_mli7a(data);
	// command_tree(data);
	// execute(data);
	clear_command_tree(&data->tokens);
	clear_command_tree(&data->tree);
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
			exit(1);
		}
		free(line);
		line = NULL;
		data->line = NULL;
	}
}

void	init_data(t_shell *data, char **env)
{
	data->number_of_commands = 0;
	data->env_list = NULL;
	get_env(data, env);
	data->tokens = NULL;
	data->pipes = NULL;
	data->tree = NULL;
	data->pids = NULL;
	data->line = NULL;
	data->status = 0;
	data->env = env;
}

int	main(int ac, char **av, char **env)
{
	t_shell	data;

	(void)av;
	if (ac != 1)
		throw_error("minishell accepts no arguments");
	init_data(&data, env);
	// signals();
	read_line(&data);
}
