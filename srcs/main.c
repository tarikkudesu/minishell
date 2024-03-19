/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:26:15 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/17 19:50:15 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_data(t_shell *data, char **env)
{
	data->number_of_commands = 0;
	data->env_list = NULL;
	if (get_env(data, env))
		(ft_putendl_fd(ERR_MAL, 2), exit(1));
	data->tokens = NULL;
	data->pipes = NULL;
	data->tree = NULL;
	data->line = NULL;
	data->status = 0;
	data->env = env;
}

int	main(int ac, char **av, char **env)
{
	t_shell	data;

	(void)av;
	if (ac != 1)
		throw_error(ERR_ERG);
	init_data(&data, env);
	signals();
	read_line(&data);
	clear_command_tree(&data.tokens);
	clear_command_tree(&data.tree);
	env_clear(&data.env_list);
}
