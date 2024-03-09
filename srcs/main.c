/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:26:15 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/09 19:24:59 by tamehri          ###   ########.fr       */
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
			ft_throw("ERROR_SUBSTR_GET_ENV");
		value = ft_strdup(start + 1);
		if (!value)
			ft_throw("ERROR_STRDUP_GET_ENV");
		node = env_new(name, value);
		if (!node)
			ft_throw("ERROR_ENV_NEW_GET_ENV");
		env_add_back(&data->env_list, node);
	}
}

void	minishell(t_shell *data)
{

	if (lexer(data))
        return ;
	// while (token) {
	// 	printf("\t\t[\033[1;32m  %s  \033[0m]\n", token->string);
	// 	token = token->right;
	// }
    check_syntax(data);
    command_tree(data);
	execute(data);
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
		if (!ft_strncmp(line, "exit", ft_strlen(line)) && ft_strlen(line) == 4)
			return (free(line), ft_exit());
		data->line = line;
		minishell(data);
		free(line);
		line = NULL;
		data->line = NULL;
		tokenclear(&data->token);
	}
}

void	init_data(t_shell *data, char **env)
{
	data->env_list = NULL;
	get_env(data, env);
	data->pipes = NULL;
	data->token = NULL;
	data->line = NULL;
	data->pids = NULL;
	data->status = 1000;
	data->env = env;
}

int	main(int ac, char **av, char **env)
{
	t_shell	data;

	(void)av;
	if (ac != 1)
		ft_throw("minishell accepts no arguments");
	init_data(&data, env);
	// signals();
	read_line(&data);
}
