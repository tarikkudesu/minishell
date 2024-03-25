/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:13:47 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/04/01 17:18:59 by tamehri          ###   ########.fr       */
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

	if (!argument[0])
	{
		ft_putstr_fd("\n", 1);
		if (data->cmd_nbr > 1)
			exit(0);
		return ;
	}
	i = -1;
	while (argument[++i])
		if (!is_echo_option(argument[i]))
			break ;
	b = i;
	while (argument[i])
	{
		ft_putstr_fd(argument[i++], 1);
		if (argument[i])
			ft_putstr_fd(" ", 1);
	}
	if (!b)
		write(1, "\n", 1);
	return (data->status = 0, exit_if(data->cmd_nbr, 0));
}
