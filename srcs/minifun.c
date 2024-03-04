/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minifun.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:57:51 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/03 19:11:01 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_operator(int c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	is_sep(int c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else if (c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

int	bunny_ears(char **s, char c)
{
	(*s)++;
	while (**s && **s != c)
		(*s)++;
	return (1);
}
