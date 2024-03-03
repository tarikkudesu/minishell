/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:53:20 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/03 14:16:08 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	evaluate_len(char *str, int *i)
{
	int		len;
	char	*var;
	char	*val;

	len = 0;
	while (*(str + len) && ft_isalnum(*(str + len)))
		len++;
	(*i) += len + 1;
	var = ft_substr(str, 0, len);
	if (!var)
		return (0);
	val = getenv(var);
	if (!val)
		return (0);
	return (free(var), ft_strlen(val));
}

static int	eval(char **pop, char *str, int *i, int *j)
{
	int		x;
	int		len;
	char	*var;
	char	*val;

	x = 0;
	len = 0;
	while (*(str + len) && ft_isalnum(*(str + len)))
		len++;
	(*i) += len + 1;
	var = ft_substr(str, 0, len);
	if (!var)
		return (0);
	val = getenv(var);
	if (!val)
		return (0);
	while (*(val + x))
	{
		*(*pop + *j) = *(val + x);
		(*j)++;
		x++;
	}
	return (1);
}

static int	find_len(char *str)
{
	int		i;
	char	c;
	int		len;

	i = 0;
	len = 0;
	while (*(str + i))
	{
		c = 0;
		(*(str + i) == '$' && (len += evaluate_len(str + i + 1, &i)));
		(*(str + i) != '$' && (++len) && (++i));
		if (*(str + i) && (*(str + i) == '\'' || *(str + i) == '\"'))
			c = *(str + i++);
		while (c && *(str + i) && *(str + i) != c)
		{
			(c == '\"' && *(str + i) == '$'
				&& (len += evaluate_len(str + i + 1, &i)));
			((c != '\"' || *(str + i) != '$') && (++len) && (++i));
		}
		if (*(str + i) && (*(str + i) == '\'' || *(str + i) == '\"'))
			i++;
	}
	return (len);
}

static int	is_operator(int c)
{
	return (c == '>' || c == '<' || c == '|');
}

char	*ft_strpop(char *s)
{
	int		i;
	int		j;
	char	c;
	char	*pop;

	pop = malloc(sizeof(char) * (find_len(s) + 1));
	if (!pop)
		return (NULL);
	i = 0;
	j = 0;
	while (*(s + i))
	{
		c = 0;
		while (*(s + i) && !is_operator(*(s + i)) && *(s + i) != '\"' && *(s + i) != '\'')
			((*(s + i) == '$' && eval(&pop, s + i + 1, &i, &j)),
				(*(s + i) != '$' && (*(pop + j++) = *(s + i++))));
		if (*(s + i))
		{
			while (*(s + i) && is_operator(*(s + i)))
					*(pop + j++) = *(s + i++);
			if (*(s + i) == '\"' || *(s + i) == '\'')
				c = *(s + i++);
		}
		while (c && *(s + i) && *(s + i) != c)
		{
			(c == '\"' && *(s + i) == '$' && eval(&pop, s + i + 1, &i, &j));
			((c == '\"' && *(s + i) != '$' && *(s + i) != '\"')
				&& (*(pop + j++) = *(s + i++)));
		}
	}
	*(pop + j) = '\0';
	return (free(s), s = NULL, pop);
}
