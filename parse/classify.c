/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:32:32 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/23 14:00:32 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	variable_len(char *str)
{
	int	c;
	int	i;

	i = 0;
	str += 2;
	while ((*str && ft_isalnum(*str)) || *str == '\'' || *str == '"')
	{
		c = 0;
		if (*str == '\'' || *str == '"')
		{
			c = *str++;
			while (*str && *str++ != c)
				i++;
			str++;
		}
		else if (*str)
		{
			str++;
			i++;
		}
	}
	return (i);
}

static char	*variable(char *s, int *i)
{
	int		c;
	int		j;
	char	*name;

	name = malloc(sizeof(char) * (variable_len(s) + 1));
	if (!name)
		return (NULL);
	(*i) += 2;
	j = 0;
	while ((*(s + *i) && ft_isalnum(*s)) \
		|| *(s + *i) == '\'' || *(s + *i) == '"')
	{
		c = 0;
		if (*(s + *i) == '\'' || *(s + *i) == '"')
		{
			c = *(s + (*i)++);
			while (*(s + *i) && *(s + *i) != c)
				*(name + j++) = *(s + (*i)++);
			(*i)++;
		}
		else if (*(s + *i))
			*(name + j++) = *(s + (*i)++);
	}
	return (*(name + j) = '\0', name);
}

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
		if (*(string + 1) == '?')
			len++;
		else if (*(string + 1) == '\'' || *(string + 1) == '"')
			return (variable(string, index));
		while (*(string + len) && (ft_isalnum(*(string + len)) \
			|| *(string + len) == '_'))
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

void	token_stat(t_shell *data, t_tokens *token)
{
	if (data->stat == GENERAL && (token->class == QUOTE \
		|| token->class == DQUOTE))
	{
		if (token->class == DQUOTE)
			data->stat = INDQUOTE;
		else
			data->stat = INQUOTE;
	}
	else if (data->stat == INDQUOTE && token->class == DQUOTE)
		data->stat = GENERAL;
	else if (data->stat == INQUOTE && token->class == QUOTE)
		data->stat = GENERAL;
	token->stat = data->stat;
}
