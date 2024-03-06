/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:26:15 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/06 10:56:52 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	minishell(t_shell *data)
{
	// t_tokens *tmp;

	lexer(data);
	// tmp = data->token;
	// while (tmp)
	// {
	// 	printf("[%d] class : %d, token : |\033[1;32m%s\033[0m|\n", tmp->index, tmp->class, tmp->string);
	// 	tmp = tmp->next;
	// }

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
			return (free(line), exit(EXIT_SUCCESS));
		data->line = line;
		minishell(data);
		free(line);
		line = NULL;
		data->line = NULL;
		tokenclear(&data->token);
	}
}
void	f() {system("leaks minishell");}

int main(int ac, char **av, char **env)
{
	t_shell	data;
atexit(f);
	(void)ac, (void)av, (void)env;
	if (ac != 1)
		return (throw_error("Error "));
	read_line(&data);
	return (0);
	return (0);
}
