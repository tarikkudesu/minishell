/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minifun.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:30:43 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/21 11:35:43 by tamehri          ###   ########.fr       */
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

int	class_operator(t_tokens *token)
{
	if (token->class == IN_RED || token->class == OUT_RED \
		|| token->class == HEREDOC || token->class == APPEND \
		|| token->class == PIPE)
		return (1);
	return (0);
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

int	skip(t_tokens *token)
{
	if (token->stat == INDQUOTE && token->class == DQUOTE)
		return (1);
	else if (token->stat == INQUOTE && token->class == QUOTE)
		return (1);
	else if (token->stat == GENERAL && token->class == QUOTE)
		return (1);
	else if (token->stat == GENERAL && token->class == DQUOTE)
		return (1);
	return (0);
}

int	exclude(t_tokens *token)
{
	if (token->stat == GENERAL)
	{
		if (token->class == WHITESPACE || token->class == PIPE \
			|| token->class == IN_RED || token->class == OUT_RED \
			|| token->class == HEREDOC || token->class == APPEND)
			return (1);
	}
	return (0);
}
