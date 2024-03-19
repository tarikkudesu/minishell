/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:38:30 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/19 17:59:52 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_all_num(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

void	ft_exit(t_shell *data, char **args)
{
	ft_putendl_fd(" exit", 1);
	if (!args[1])
		exit(0);
	if (args[1] && !is_all_num(args[1]))
		(ft_putendl_fd(" numeric argument required", 2),
			exit(255));
	else if (args[2])
		(ft_putendl_fd(" minishell: exit: too many arguments", 2), \
		data->status = 1);
	else
		exit(ft_atoi(args[1]) % 256);
}
