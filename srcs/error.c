/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:39:48 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/06 10:22:24 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	throw_error(char *str)
{
	ft_putendl_fd(str, 2);
	return (1);
}

void	ft_throw(char *strerr)
{
	printf("%s\n", strerr);
	exit(EXIT_FAILURE);
}
