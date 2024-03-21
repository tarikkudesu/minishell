/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:44:38 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/21 16:34:03 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_sig;

int	check_quoting(char *str)
{
	int	c;

	while (*str)
	{
		c = 0;
		if (*str == '\'' || *str == '"')
		{
			c = *str;
			str++;
			while (*str && *str != c)
				str++;
			if (!*str)
				return (1);
			str++;
		}
		else
			str++;
	}
	return (0);
}

int	minishell(t_shell *data)
{
	if (check_quoting(data->line))
		return (ft_putendl_fd(ERR_UNCLOSED_QUOTES, 2), 1);
	if (lexer(data) || pars(data) || syntax(data))
		return (g_sig = 0, 1);
	command_tree(data);
	execute(data);
	if (data->cmd_nbr > 1)
		(free_2d_int(data->pipes, data->cmd_nbr - 1), \
		data->pipes = NULL);
	return (g_sig = 0);
}

void	read_line(t_shell *data)
{
	char	*line;

	while (1)
	{
		line = readline("\033[1;32m➜  \033[1;32mminishell \033[0m");
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
