/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:25:24 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/20 14:30:47 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_word(char *str, int ascii)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str[i])
	{
		while (str[i] && str[i] != ascii)
			i++;
		if (str[i])
			word++;
		while (str[i] && str[i] == ascii)
			i++;
	}
	return (word);
}

fill_args(args, token->string, &i);