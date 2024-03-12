/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minifun.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:30:43 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/12 17:09:19 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (*(s1 + i) && *(s1 + i) && *(s1 + i) == *(s2 + i))
		i++;
	return (*(s1 + i) - *(s2 + i));
}

int	meta_char(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' \
		|| c == '\r' || c == '\v' || c == '\f' \
		|| c == '>' || c == '<' || c == '|' \
		|| c == '"' || c == '\'' || c == '$')
		return (1);
	return (0);
}

int	add(t_tokens *token)
{
	if (token->class == WORD)
		return (1);
	else if (token->stat == GENERAL)
	{
		if (token->class != WHITESPACE && \
			token->class != QUOTE && token->class != DQUOTE)
			return (1);
	}
	else if (token->stat != GENERAL)
	{
		if (token->class != QUOTE && token->class != DQUOTE)
			return (1);
	}
	return (0);
}

int	skip(t_tokens *token)
{
	if (token->class == QUOTE || token->class == DQUOTE)
		return (1);
	return (0);
}

int	keep(t_tokens *token)
{
	if (token->class == WORD || token->class == ENV)
		return (1);
	else if (token->stat != GENERAL)
		return (1);
	return (0);
}
