/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:26:15 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/11 10:27:40 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_env(t_shell *data, char **env)
{
	int		i;
	char	*name;
	char	*value;
	char	*start;
	t_env	*node;

	i = -1;
	while (env[++i])
	{
		start = ft_strchr(env[i], '=');
		name = ft_substr(env[i], 0, (start - env[i]));
		if (!name)
			throw_error("ERROR_SUBSTR_GET_ENV");
		value = ft_strdup(start + 1);
		if (!value)
			throw_error("ERROR_STRDUP_GET_ENV");
		node = env_new(name, value);
		if (!node)
			throw_error("ERROR_ENV_NEW_GET_ENV");
		env_add_back(&data->env_list, node);
	}
}

void fonction_mli7a(t_shell *data)
{
	t_tokens	*token;
	token = data->tokens;

	while (token)
	{
		printf("\t\t[\033[1;32m\t%s\t\033[0m]\ttype : \t|\033[1;33m%c\033[0m|\t stat : |\033[1;34m%c\033[0m|\n", token->string, token->class, token->stat);
		token = token->right;
	}
	printf("-------------------------------------------------------------------\n");
	// token = data->tree;
	// while (token)
	// {
	// 	printf("\t\t[\033[1;32m%s\033[0m]class : \t|\033[1;33m%c\033[0m|\n", token->string, token->class);
	// 	token = token->right;
	// }
}

void	minishell(t_shell *data)
{
	// if (lexer(data) || pars(data) || check_syntax(data))
	// 	return ;
	printf("%d\n", lexer(data));
	// printf("%d\n", pars(data));
	// check_syntax(data);
	fonction_mli7a(data);
	// command_tree(data);
	// execute(data);
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
			minishell(data);
			clear_command_tree(&data->tokens);
			clear_command_tree(&data->tree);
		}
		free(line);
		line = NULL;
		data->line = NULL;
		// system("echo '\033[1;33m'; leaks minishell; echo '\033[0m'");
	}
}

void	init_data(t_shell *data, char **env)
{
	data->env_list = NULL;
	get_env(data, env);
	data->stat = GENERAL;
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
	// signals();
	read_line(&data);
}
