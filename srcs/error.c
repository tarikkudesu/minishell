/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:39:48 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/19 18:25:02 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	my_free(char *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}

void	free_2d_int(int **free2d, int nb_pipe)
{
	int	i;

	i = -1;
	while (++i < nb_pipe)
		(free(free2d[i]), free2d[i] = NULL);
	(free(free2d), free2d = NULL);
}

void	free_2d_char(char **free2d)
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
	ft_putendl_fd(strerr, 2);
	exit(status);
}
