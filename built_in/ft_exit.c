/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:38:30 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/14 23:47:26 by ooulcaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_all_num(char *str)
{
	while (*str)
		if ((*str < '0' || *str++ > '9'))
			return (0);
	return (1);
}

void	ft_exit(char **args)
{
	ft_putendl_fd("exit", 1);
	if (!args[1])
		exit(0);
	if (args[1] && !is_all_num(args[1]))
		(printf("mininshell: %s: numeric argument required\n", args[1]),
			exit(255));
	else if (args[2])
		printf("minishell: exit: too many arguments\n");
	else
		exit(ft_atoi(args[1]) % 256);
}
