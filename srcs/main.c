/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:26:15 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/24 18:19:51 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_data(t_shell *data, char **env)
{
	data->cmd_nbr = 0;
	data->pwd = getcwd(NULL, 0);
	data->env_list = NULL;
	get_env(data, env, env, NULL);
	data->tokens = NULL;
	data->pipes = NULL;
	data->tree = NULL;
	data->line = NULL;
	data->doc_fd = -1;
	data->status = 0;
	data->exp = '0';
	data->env = env;
}

int	main(int ac, char **av, char **env)
{
	t_shell	data;

	(void)av;
	if (ac != 1)
		(ft_putendl_fd(ERR_ARG, 2), exit(1));
	init_data(&data, env);
	read_line(&data);
	clear_command_tree(&data.tokens);
	clear_command_tree(&data.tree);
	env_clear(&data.env_list);
	return (0);
}
