/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:39:48 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/11 10:24:42 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_2d(char **free2d)
{
	int	i;

	i = -1;
	while (free2d[++i])
		free(free2d[i]);
	free(free2d);
}

int	throw_error(char *str)
{
	ft_putendl_fd(str, 2);
	return (1);
}

void	ft_throw(char *strerr, int status)
{
	printf("%s\n", strerr);
	exit(status);
}

