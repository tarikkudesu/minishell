/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:26:15 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/15 13:33:43 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void fonction_mli7a(t_shell *data)
{
	t_tokens	*token;
	token = data->tokens;

	while (token)
	{
		printf("\t\t[\033[1;32m\t%s\t\033[0m]\ttype : \t|\033[1;33m%c\033[0m|\t stat : |\033[1;34m%c\033[0m|\n", token->string, token->class, token->stat);
		token = token->right;
	}
	printf("------------------------------------------------------------\n");
	token = data->tree;
	while (token)
	{
		printf("\t\t[\033[1;32m%s\033[0m]class : \t|\033[1;33m%c\033[0m|\t stat : |\033[1;34m%c\033[0m|\n", token->string, token->class, token->stat);
		token = token->right;
	}
}

void	minishell(t_shell *data)
{
	if (lexer(data))
		return ;
	if (pars(data))
		return ;
	if (check_syntax(data))
		return ;
	// fonction_mli7a(data);
	command_tree(data);
	execute(data);
}

void	print_env(char **env)
{
	for (int i = 0; env[i]; i++) {
		printf("\033[33m%s\033[0m\n", env[i]);
	}
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
			// print_env(env_to_array(data->env_list));
			clear_command_tree(&data->tokens);
			clear_command_tree(&data->tree);
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
	data->line = NULL;
	data->pids = NULL;
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
	signals();
	read_line(&data);
}
