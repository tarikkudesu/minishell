/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:56:06 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/04 13:53:17 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	clen(char *line)
{
	int	i;

	i = 0;
	while (*line)
	{
		while (*line && is_sep(*line))
			line++;
		if (*line && !is_operator(*line))
		{
			while (*line && !is_sep(*line) && !is_operator(*line))
			{
				((*line == '\"' || *line == '\'') && bunny_ears(&line, *line));
				line++;
			}
			i++;
		}
		if (*line && is_operator(*line))
		{
			while (*line && is_operator(*line))
				line++;
			i++;
		}
	}
	return (i);
}

int	tablen2(char const *s, int *index)
{
	int		i;

	i = *index;
	while (*(s + i) && is_operator(*(s + i)))
		i++;
	return (i - *index);
}

int	tablen(char const *s, int *index)
{
	int		i;

	i = 0;
	while (*(s + (*index)) && is_sep(*(s + (*index))))
		(*index)++;
	if (is_operator(*(s + (*index))))
		return (tablen2(s, index));
	i = *index;
	while (*(s + i) && !is_sep(*(s + i)) && !is_operator(*(s + i)))
	{
		if (*(s + i) == '\"')
		{
			i++;
			while (*(s + i) && *(s + i) != '\"')
				i++;
		}
		else if (*(s + i) == '\'')
		{
			i++;
			while (*(s + i) && *(s + i) != '\'')
				i++;
		}
		i++;
	}
	return (i - *index);
}

char	*init_token(char const *s, int *index, int wlen)
{
	int		i;
	char	*word;

	word = malloc(sizeof(char) * (wlen + 1));
	if (!word)
		return (NULL);
	i = -1;
	while (++i < wlen)
		*(word + i) = *(s + (*index)++);
	*(word + i) = '\0';
	return (word);
}

void	shell_split(t_shell *data)
{
	int			i;
	char		*str;
	int			flen;
	int			index;
	t_tokens	*token;

	i = -1;
	index = 0;
	flen = clen(data->line);
	while (++i < flen)
	{
		str = init_token(data->line, &index, tablen(data->line, &index));
		if (!str)
			return ;
		token = tokennew(str);
		if (!token)
			return ;
		tokenadd_back(&data->token, token);
		process_token(token);
	}
}
