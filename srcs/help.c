/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:53:20 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/03 01:25:15 by ooulcaid         ###   ########.fr       */
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
		(*(str + i) && (c = *(str + i++)));
		while (c && *(str + i) && *(str + i) != c)
		{
			(c == '\"' && *(str + i) == '$'
				&& (len += evaluate_len(str + i + 1, &i)));
			((c != '\"' || *(str + i) != '$') && (++len) && (++i));
		}
	}
	return (len);
}

char	*ft_strpop(char *str)
{
	int		i;
	int		j;
	char	c;
	char	*pop;

	pop = malloc(sizeof(char) * (find_len(str) + 1));
	if (!pop)
		return (NULL);
	i = 0;
	j = 0;
	while (*(str + i))
	{
		c = 0;
		while (*(str + i) && *(str + i) != '\"' && *(str + i) != '\'')
			((*(str + i) == '$' && eval(&pop, str + i + 1, &i, &j)),
				(*(str + i) != '$' && (*(pop + j++) = *(str + i++))));
		(*(str + i) && (c = *(str + i++)));
		while (c && *(str + i) && *(str + i) != c)
		{
			(c == '\"' && *(str + i) == '$' && eval(&pop, str + i + 1, &i, &j));
			((c == '\"' && *(str + i) != '$' && *(str + i++) != '\"')
				&& (*(pop + j++) = *(str + i - 1)));
		}
	}
	return (free(str), str = NULL, *(pop + j) = '\0', pop);
}
