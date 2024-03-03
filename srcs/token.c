/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:56:06 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/03 14:16:52 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_sep(int c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else if (c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

static char	**ft_error(char **tab)
{
	int	i;

	i = 0;
	while (*(tab + i))
		free(*(tab + i++));
	free(tab);
	return (NULL);
}

static void	bunny_ears(char **s, char c)
{
	(*s)++;
	while (**s && **s != c)
		(*s)++;
}
static int	is_operator(int c)
{
	return (c == '>' || c == '<' || c == '|');
}

static int	clen(char *line)
{
	int	i;

	i = 0;
	while (*line)
	{
		while (*line && is_sep(*line))
			line++;
		if (*line)
		{
			i++;
			while (*line && !is_sep(*line) && !is_operator(*line))
			{
				if (*line == '\"' || *line == '\'')
					bunny_ears(&line, *line);
				line++;
			}
			if (*line && is_operator(*line))
			{
				((*line == '<' && *(line + 1) && *(line + 1) == '<' && line++),
				(*line == '>' && *(line + 1) && *(line + 1) == '>' && line++));
				i++;
				line++;
			}
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

char	*ft_itab(char const *s, int *index, int wlen)
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

char	**shell_split(char *line)
{
	int		flen;
	int		i;
	int		index;
	char	**tab;

	if (!line)
		return (NULL);
	i = -1;
	index = 0;
	flen = clen(line);
	tab = malloc(sizeof(char *) * (flen + 1));
	if (!tab)
		return (NULL);
	while (++i < flen)
	{
		*(tab + i) = ft_itab(line, &index, tablen(line, &index));
		if (!*(tab + i))
			return (ft_error(tab));
		*(tab + i) = ft_strpop(*(tab + i));
	}
	*(tab + i) = 0;
	return (NULL);
	return (tab);
}
