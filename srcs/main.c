/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:26:15 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/03 20:39:22 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	minishell(t_shell *data)
{
	t_tokens *tmp;

	shell_split(data);
	tmp = data->token;
	while (tmp)
	{
		printf("class : %d, token : |\033[1;32m%s\033[0m|\n", tmp->class, tmp->token);
		tmp = tmp->next;
	}
	tokenclear(&data->token);
}

void	read_line(t_shell *data)
{
	char	*line;

	while (1)
	{
		line = readline("\033[1;32m➜  \033[1;36mminishell \033[0m");
		if (!line)
			return ;
		if (!ft_strncmp(line, "exit", ft_strlen(line)) && ft_strlen(line))
			return ;
		data->line = line;
		minishell(data);
		free(line);
		data->line = NULL;
		line = NULL;
	}
}

int main(int ac, char **av, char **env)
{
	t_shell	data;

	if (ac != 1)
	{
		av++;
		env++;
		ft_putendl_fd("Error", 2);
		return (1);
	}
	read_line(&data);
	return (0);
}
