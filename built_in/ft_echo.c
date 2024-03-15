/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:13:47 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/14 15:23:36 by ooulcaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_echo_option(char *option)
{
	int	i;

	i = 0;
	if (option[i] != '-')
		return (0);
	while (option[++i])
	{
		if (option[i] != 'n')
			return (0);
	}
	return (1);
}

void	ft_echo(t_shell *data, char **argument)
{
	int	i;
	int	b;

	i = -1;
	while (argument[++i])
		if (!is_echo_option(argument[i]))
			break ;
	b = i;
	while (argument[i])
		(ft_putstr_fd(argument[i], 1), ft_putstr_fd(" ", 1), i++);
	if (!b)
		write(1, "\n", 1);
	data->status = 0;
}

// int	main(int ac, char **av) // to delete it
// {
// 	if (ac)
// 		ft_echo(av + 1);
// }