/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:49:09 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/07 19:27:44 by ooulcaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// This function will return the lenght of a token if it is an operator
static int	token_len2(char const *s, int *index)
{
	int		len;

	len = *index;
	while (*(s + len) && is_operator(*(s + len)))
		len++;
	return (len - *index);
}

// this function will caculate the lenght of each token
static int	token_len(char const *s, int *index)
{
	int		len;

	len = 0;
	while (*(s + (*index)) && is_space(*(s + (*index))))
		(*index)++;
	if (is_operator(*(s + (*index))))
		return (token_len2(s, index));
	len = *index;
	while (*(s + len) && !is_space(*(s + len)) && !is_operator(*(s + len)))
	{
		if (*(s + len) == '\"')
		{
			len++;
			while (*(s + len) && *(s + len) != '\"')
				len++;
		}
		else if (*(s + len) == '\'')
		{
			len++;
			while (*(s + len) && *(s + len) != '\'')
				len++;
		}
		len++;
	}
	return (len - *index);
}

// this function will retreive the next token
char	*init_token(char const *s, int *index, int lenght)
{
	int		i;
	char	*word;

	word = malloc(sizeof(char) * (lenght + 1));
	if (!word)
		return (NULL);
	i = -1;
	while (++i < lenght)
		*(word + i) = *(s + (*index)++);
	*(word + i) = '\0';
	return (word);
}

// this function will iterate over the line and find the number of tokens in it
int	get_number_of_tokens(char *line)
{
	int	number_of_tokens;

	number_of_tokens = 0;
	while (*line)
	{
		while (*line && is_space(*line))
			line++;
		if (*line && !is_operator(*line))
		{
			while (*line && !is_space(*line) && !is_operator(*line))
			{
				((*line == '\"' || *line == '\'') \
				&& bunny_ears(&line, *line));
				line++;
			}
			number_of_tokens++;
		}
		if (*line && is_operator(*line))
		{
			while (*line && is_operator(*line))
				line++;
			number_of_tokens++;
		}
	}
	return (number_of_tokens);
}

/*
	this function will proccess the given line and split into tokens while 
	removing single quotes quotes and single quotes and expand envirement 
	variables
*/
int	lexer(t_shell *data)
{
	int			i;
	char		*str;
	int			index;
	t_tokens	*token;

	i = -1;
	index = 0;
	data->number_of_tokens = get_number_of_tokens(data->line);
	data->token = NULL;
	while (++i < data->number_of_tokens)
	{
		str = init_token(data->line, &index, token_len(data->line, &index));
		if (!str)
			return (throw_error(ERR_MAL));
		token = tokennew(str);
		if (!token)
			return (free(str), throw_error(ERR_MAL));
		token->index = i;
		tokenadd_back(&data->token, token);
		if (process_token(data, token))
			return (1);
	}
	return (0);
}
