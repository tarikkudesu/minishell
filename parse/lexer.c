/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:30:06 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/12 17:08:53 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*meta_char_string(char *string, int *index)
{
	int	len;

	if (*string == ' ' || *string == '\t' || *string == '\n' \
		|| *string == '\r' || *string == '\v' || *string == '\f' \
		|| *string == '|' || *string == '"' || *string == '\'')
		return ((*index)++, ft_substr(string, 0, 1));
	else if ((*string == '<' && *(string + 1) == '<') \
		|| (*string == '>' && *(string + 1) == '>'))
		return ((*index) += 2, ft_substr(string, 0, 2));
	else if (*string == '>' || *string == '<')
		return ((*index) += 1, ft_substr(string, 0, 1));
	else if (*string == '$')
	{
		len = 1;
		if (*(string + 1) == '$')
			len++;
		while (*(string + len) && !meta_char(*(string + len)))
			len++;
		(*index) += len;
		return (ft_substr(string, 0, len));
	}
	return (NULL);
}

void	token_class(t_tokens *token)
{
	if (!ft_strcmp(token->string, "|"))
		token->class = PIPE;
	else if (!ft_strcmp(token->string, "'"))
		token->class = QUOTE;
	else if (!ft_strcmp(token->string, "\""))
		token->class = DQUOTE;
	else if (!ft_strcmp(token->string, ">>"))
		token->class = APPEND;
	else if (!ft_strcmp(token->string, "<<"))
		token->class = HEREDOC;
	else if (!ft_strcmp(token->string, "<"))
		token->class = IN_RED;
	else if (!ft_strcmp(token->string, ">"))
		token->class = OUT_RED;
	else if (!ft_strcmp(token->string, " "))
		token->class = WHITESPACE;
	else if (!ft_strncmp(token->string, "$", 1))
		token->class = ENV;
	else
		token->class = WORD;
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

t_tokens	*init_token(t_shell *data, char *line, int *index)
{
	char		*string;
	t_tokens	*token;

	string = token_string(line + *index, index);
	if (!string)
		return (ft_putendl_fd(ERR_MAL, 2), NULL);
	token = tokennew(string);
	if (!token)
		return (ft_putendl_fd(ERR_MAL, 2), NULL);
	token_class(token);
	if (token->class == QUOTE || token->class == DQUOTE)
	{
		if (data->stat == INDQUOTE || data->stat == INQUOTE)
			data->stat = GENERAL;
		else if (token->class == DQUOTE)
			data->stat = INDQUOTE;
		else if (token->class == QUOTE)
			data->stat = INQUOTE;
	}
	token->stat = data->stat;
	return (token);
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
		token = init_token(data, data->line, &index);
		if (!token)
			return (1);
		tokenadd_back(&data->tokens, token);
	}
	return (0);
}
