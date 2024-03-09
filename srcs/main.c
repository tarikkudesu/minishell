/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:26:15 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/07 19:55:35 by ooulcaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_env()
{

}

void	minishell(t_shell *data)
{
	t_tokens	*token;

	if (lexer(data))
        return ;
	token = data->token;
	while (token) {
		printf("\t\t[\033[1;32m  %s  \033[0m]\n", token->string);
		token = token->right;
	}
    // check_syntax(data);
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
		if (!ft_strncmp(line, "exit", ft_strlen(line)) && ft_strlen(line))
			return (free(line), ft_exit());
		data->line = line;
		minishell(data);
		free(line);
		line = NULL;
		data->line = NULL;
		tokenclear(&data->token);
		// env_clear(&data->env);
	}
}

void	init_data(t_shell *data, char **env)
{
	// data->env_list = get_env(env);
	data->pipes = NULL;
	data->token = NULL;
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
		ft_throw("minishell accepts no arguments");
	init_data(&data, env);
	// signals();
	read_line(&data);
}
