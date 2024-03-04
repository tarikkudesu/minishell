/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:53:20 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/04 13:54:37 by tamehri          ###   ########.fr       */
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

static int	eval(char **pop, char *str, int *j)
{
	int		x;
	int		len;
	char	*var;
	char	*val;

	x = 0;
	len = 0;
	while (*(str + len) && ft_isalnum(*(str + len)))
		len++;
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

// char	*ft_strpop(char *s)
// {
// 	int		i;
// 	int		j;
// 	char	c;
// 	char	*pop;

// 	pop = malloc(sizeof(char) * (find_len(s) + 1));
// 	if (!pop)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (*(s + i))
// 	{
// 		c = 0;
// 		while (*(s + i) && !is_operator(*(s + i)) && *(s + i) != '\"' && *(s + i) != '\'')
// 			((*(s + i) == '$' && eval(&pop, s + i + 1, &i, &j)),
// 				(*(s + i) != '$' && (*(pop + j++) = *(s + i++))));
// 		if (*(s + i))
// 		{
// 			while (*(s + i) && is_operator(*(s + i)))
// 					*(pop + j++) = *(s + i++);
// 			if (*(s + i) == '\"' || *(s + i) == '\'')
// 				c = *(s + i++);
// 		}
// 		while (c && *(s + i) && *(s + i) != c)
// 		{
// 			(c == '\"' && *(s + i) == '$' && eval(&pop, s + i + 1, &i, &j));
// 			((c == '\"' && *(s + i) != '$' && *(s + i) != '\"')
// 				&& (*(pop + j++) = *(s + i++)));
// 			((c == '\'' && *(s + i) != '\'')
// 				&& (*(pop + j++) = *(s + i++)));
// 		}
// 	}
// 	return (free(s), s = NULL, *(pop + j) = '\0', pop);
// }

void	simple_word(char **s, char **tmp, int *j)
{	
	while (**tmp && !is_operator(**tmp) && **tmp != '\"' && **tmp != '\'')
	{
		if (**tmp == '$')
			eval(s, *tmp + 1, j);
		else
		{
			*(*s + *j) = **tmp;
			(*j)++;
		}
		(*tmp)++;
	}
}

void	operat_word(char **s, char **tmp, int *j, char *c)
{
	if (**tmp)
	{
		while (**tmp && is_operator(**tmp))
		{
			*(*s + *j) = **tmp;
			(*tmp)++;
			(*j)++;
		}
		if (**tmp == '\"' || **tmp == '\'')
		{
			*c = **tmp;
			(*tmp)++;
		}
	}
	
}

void	quoted_word(char **s, char **tmp, int *j, char *c)
{	
	while (*c && **tmp && **tmp != *c)
	{
		if (*c == '\"')
		{
			if (**tmp == '$')
				eval(s, *tmp + 1, j);
			else if (**tmp != '$' && **tmp != '\"')
			{
				*(*s + *j) = **tmp;
				(*tmp)++;
				(*j)++;
			}
		}
		else if (*c == '\'' && **tmp != '\'')
		{
				*(*s + *j) = **tmp;
				(*tmp)++;
				(*j)++;
		}
	}
}

void	process_token(t_tokens *token)
{
	char	*tmp;
	char	*s;
	int		j;
	char	q;
	
	j = 0;
	s = malloc(sizeof(char) * (find_len(token->token) + 1));
	if (!s)
		return ;
	tmp = token->token;
	while (*tmp)
	{
		q = 0;
		simple_word(&s, &tmp, &j);
		operat_word(&s, &tmp, &j, &q);
		quoted_word(&s, &tmp, &j, &q);
	}
	free(token->token);
	token->token = s;
}
