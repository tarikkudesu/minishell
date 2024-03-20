/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:30:06 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/20 14:31:25 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_quoting(char *str)
{
	int	c;

	while (*str)
	{
		c = 0;
		if (*str == '\'' || *str == '"')
		{
			c = *str;
			str++;
			while (*str && *str != c)
				str++;
			if (!*str)
				return (1);
			str++;
		}
		else
			str++;
	}
	return (0);
}

char	*token_string(char *string, int *index)
{
	int		i;
	char	*word;

	i = 0;
	if (!meta_char(*string))
	{
		while (*(string + i) && !meta_char(*(string + i)))
			i++;
		(*index) += i;
		word = ft_substr(string, 0, i);
		if (!word)
			return (NULL);
		return (word);
	}
	return (meta_char_string(string, index));
}

t_tokens	*init_token(t_shell *data, char *line, int *index, int t)
{
	char		*string;
	t_tokens	*token;

	string = token_string(line + *index, index);
	if (!string)
		return (NULL);
	token = tokennew(string);
	if (!token)
		return (free(string), NULL);
	if (!t)
	{
		token_class(token);
		token_stat(data, token);
	}
	else
	{
		if (!ft_strcmp(token->string, " "))
			token->class = WHITESPACE;
		else
			token->class = WORD;
		token->stat = data->stat;
	}
	return (token);
}

/*
	If the token is an envirement vaiable it expanded and broken into tokens
	and added to the linked list.
*/
int	env_lexer(t_shell *data, char *line)
{
	int			index;
	t_tokens	*token;

	index = 0;
	while (line[index])
	{
		token = init_token(data, line, &index, 1);
		if (!token)
			return (1);
		tokenadd_back(&data->tokens, token);
	}
	return (0);
}

/*
	The Lexer : this function will retrieve the next token and add it
	to a linked list, a token can be a word, an operator (<, >, <<, >>, |),
	an env ($VAR) or a quote (", ')
*/
int	lexer(t_shell *data)
{
	int			index;
	t_tokens	*token;

	index = 0;
	while (data->line[index])
	{
		token = init_token(data, data->line, &index, 0);
		if (!token)
			return (throw_error(ERR_MAL));
		if (token->class == HEREDOC && token->stat == GENERAL)
		{
			tokenadd_back(&data->tokens, token);
			if (heredoc_init(data, &index))
				return (1);
		}
		else if (token->class == ENV && token->stat != INQUOTE)
		{
			if (expand(data, token) || env_lexer(data, token->string))
				return (tokenclear(&token), throw_error(ERR_MAL));
			tokenclear(&token);
		}
		else
			tokenadd_back(&data->tokens, token);
	}
	return (0);
}
