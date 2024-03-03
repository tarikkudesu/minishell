/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:26:15 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/03 00:00:23 by ooulcaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	minishell(t_shell *data)
{
	char	**tab;

	tab = shell_split(data->line);
	for (int i = 0; *(tab + i); i++)
		printf("tab %d == %s\n", i, *(tab + i));
}

void	read_line(t_shell *data)
{
	char	*line;

	while (1)
	{
		line = readline("minishell >> ");
		if (!line || !ft_strncmp(line, "exit", ft_strlen(line)))
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
