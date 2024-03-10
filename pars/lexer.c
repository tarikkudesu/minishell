/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:49:09 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/10 11:22:12 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// This function will return the lenght of a token if it is an operator
static int	token_len2(char const *s)
{
	int		len;

	len = 0;
	if (*s == '<' && *(s + 1) == '<')
		len = 2;
	else if (*s == '>' && *(s + 1) == '>')
		len = 2;
	else if (*s == '|' || *s == '>' || *s == '<')
		len = 1;
	return (len);
}

// this function will caculate the lenght of each token
static int	token_len(char const *s, int *index)
{
	int		len;
	int		c;

	len = 0;
	while (*(s + (*index)) && is_space(*(s + (*index))))
		(*index)++;
	if (is_operator(*(s + *index)))
		return (token_len2(s + *index));
	len = *index;
	while (*(s + len) && !is_space(*(s + len)) && !is_operator(*(s + len)))
	{
		if (*(s + len) == '\"' || *(s + len) == '\'')
		{
			(assign(&c, *(s + len)), assign(&len, len + 1));
			while (*(s + len) && *(s + len) != c)
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
	char	*token;

	if (!lenght)
		return (NULL);
	token = malloc(sizeof(char) * (lenght + 1));
	if (!token)
		return (NULL);
	i = -1;
	while (++i < lenght)
		*(token + i) = *(s + (*index)++);
	while (*(s + *index) && is_space(*(s + *index)))
		(*index)++;
	*(token + i) = '\0';
	return (token);
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

	i = 0;
	index = 0;
	while (data->line[index])
	{
		i++;
		str = init_token(data->line, &index, token_len(data->line, &index));
		if (!str)
			return (0);
		token = tokennew(str);
		if (token && i == 3)
			return (free(str), throw_error(ERR_MAL));
		token->index = i;
		tokenadd_back(&data->token, token);
		if (process_token(data, token))
			return (1);
	}
	return (0);
}
