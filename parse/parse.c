/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:32:45 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/17 19:54:02 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*join_tokens(t_tokens **tmp, char *string)
{
	char		*to_free;

	if (!string)
	{
		string = ft_strdup((*tmp)->string);
		if (!string)
			return (NULL);
		return (string);
	}
	to_free = string;
	string = ft_strjoin(string, (*tmp)->string);
	if (!string)
		return (free(to_free), NULL);
	free(to_free);
	return (string);
}

int	init_leaf(t_shell *data, char *string, t_tokens *class)
{
	t_tokens	*token;

	if (!string)
		return (1);
	token = tokennew(string);
	if (!token)
		return (free(string), 1);
	if (class->stat == GENERAL)
		token->class = class->class;
	else
		token->class = WORD;
	token->stat = class->stat;
	tokenadd_back(&data->tree, token);
	return (0);
}

void	add_sub_list(t_tokens **token, t_tokens *sublist)
{
	t_tokens	*tmp;
	t_tokens	*tail;

	tail = (*token)->right;
	tmp = token;
	if (!token->right)
		token = sublist;
	else
	{
		token = sublist;
		while (sublist->right)
			sublist = sublist->right;
		sublist->right = tmp->right;
	}
	free(tmp);
	tmp = NULL;
}

int	env_lexer(t_shell *data, t_tokens **tmp)
{
	int			index;
	char		*line;
	t_tokens	*token;
	t_tokens	*sub_tokens;

	index = 0;
	while ((*tmp)->string[index])
	{
		token = init_token(data, (*tmp)->string, &index);
		if (!token)
			return (throw_error(ERR_MAL));
		tokenadd_back(&sub_tokens, token);
	}
	add_sub_list(tmp, sub_tokens);
	return (0);
}

int	leaf(t_shell *data, t_tokens **tmp, int exp)
{
	t_tokens	*class;
	char		*string;

	class = *tmp;
	string = NULL;
	while (*tmp && !exclude(*tmp))
	{
		if (skip(*tmp))
			*tmp = (*tmp)->right;
		else
		{
			if (!exp && (*tmp)->class == ENV)
				if (env_lexer(data, tmp))
					return (throw_error(ERR_MAL));
			string = join_tokens(tmp, string);
			if (!string)
				return (throw_error(ERR_MAL));
			*tmp = (*tmp)->right;
		}
	}
	if (exp)
		if (heredoc(data, string))
			return (1);
	return (init_leaf(data, string, class));
}

int	pars(t_shell *data)
{
	t_tokens	*tmp;
	int			exp;

	exp = 0;
	tmp = data->tokens;
	while (tmp)
	{
		if (class_operator(tmp) && tmp->stat == GENERAL)
		{
			if (init_leaf(data, ft_strdup(tmp->string), tmp))
				return (throw_error(ERR_MAL));
			if (tmp->stat == GENERAL && tmp->class == HEREDOC)
				exp = 1;
			tmp = tmp->right;
		}
		else if (exclude(tmp))
			tmp = tmp->right;
		else
		{
			if (leaf(data, &tmp, exp))
				return (1);
			exp = 0;
		}
	}
	return (0);
}
