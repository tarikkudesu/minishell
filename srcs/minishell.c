/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:44:38 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/05 13:47:35 by tamehri          ###   ########.fr       */
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

void	process_line(t_shell *data, char *line)
{
	add_history(line);
	data->line = line;
	data->stat = GENERAL;
	minishell(data);
	(clear_command_tree(&data->tokens), data->tokens = NULL);
	(clear_command_tree(&data->tree), data->tree = NULL);
}

void	read_line(t_shell *data)
{
	int		zero;

	signals();
	while (1)
	{
		zero = dup(0);
		if (zero < 0)
			ft_throw(ERR_DUP, 1);
		signal(SIGINT, sig_h);
		data->line = readline("\033[1;32m➜  \033[1;36mminishell \033[0m");
		if (!data->line && !g_sig)
			break ;
		else if (!data->line && g_sig)
		{
			if (dup2(zero, 0) < 0)
				ft_throw(ERR_DUP2, 1);
			data->status = 1;
			g_sig = 0;
		}
		else if (data->line && *(data->line))
			process_line(data, data->line);
		(free(data->line), data->line = NULL, close(zero));
	}
	close(zero);
}
