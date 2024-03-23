/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:30:06 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/23 12:38:06 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		(token_class(token), token_stat(data, token));
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

static int	env_lexer(t_shell *data, char *line, t_tokens **tmp)
{
	int			index;
	t_tokens	*token;

	index = 0;
	if (data->exp == '1')
		return (tokenadd_back(&data->tokens, *tmp), 0);
	while (line[index])
	{
		token = init_token(data, line, &index, 1);
		if (!token)
			return (1);
		tokenadd_back(&data->tokens, token);
	}
	return (tokenclear(tmp), 0);
}

static	int	simple_cases(t_shell *data, t_tokens **token, int *index)
{
	if ((*token)->stat == GENERAL && (*token)->class == HEREDOC)
	{
		tokenadd_back(&data->tokens, (*token));
		if (heredoc_init(data, index))
			return (1);
	}
	else if ((*token)->class == ENV && (*token)->stat != INQUOTE)
	{
		if (expand(data, *token) || env_lexer(data, (*token)->string, token))
			return (tokenclear(token), throw_error(data, ERR_MAL, 1));
	}
	else
		tokenadd_back(&data->tokens, (*token));
	return (0);
}

int	lexer(t_shell *data)
{
	int			index;
	t_tokens	*token;

	index = 0;
	data->exp = '0';
	while (data->line[index])
	{
		token = init_token(data, data->line, &index, 0);
		if (!token)
			return (throw_error(data, ERR_MAL, 1));
		if (token->stat == GENERAL && class_operator(token))
			data->exp = '0';
		else if (!ft_strcmp(token->string, "export"))
			data->exp = '1';
		if (simple_cases(data, &token, &index))
			return (1);
	}
	return (data->exp = '0', 0);
}
