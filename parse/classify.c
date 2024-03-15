/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:32:32 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/15 09:39:54 by tamehri          ###   ########.fr       */
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
