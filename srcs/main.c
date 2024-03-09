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

void	minishell(t_shell *data)
{
	if (lexer(data))
        return ;
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
		if (!ft_strncmp(line, "exit", ft_strlen(line)) && ft_strlen(line))
			return (free(line), ft_exit());
		data->line = line;
		minishell(data);
		free(line);
		line = NULL;
		data->line = NULL;
		tokenclear(&data->token);
		env_clear(&data->env);
	}
}

void	f(void)
{
	system("lsof -c minishell");
}

int	main(int ac, char **av, char **env)
{
	t_shell	data;

	// atexit(f);
	signals();
	((void)ac, (void)av);
	if (ac != 1)
		return (throw_error("Error "));
	data.env = get_env(env);
	read_line(&data);
}
