/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:32:45 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/19 16:56:53 by tamehri          ###   ########.fr       */
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
	{
		string = ft_strdup("");
		if (!string)
			return (1);
		token = tokennew(string);
	}
	else
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

int	leaf(t_shell *data, t_tokens **tmp)
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
			string = join_tokens(tmp, string);
			if (!string)
				return (1);
			*tmp = (*tmp)->right;
		}
	}
	return (init_leaf(data, string, class));
}

int	pars(t_shell *data)
{
	t_tokens	*tmp;

	tmp = data->tokens;
	while (tmp)
	{
		if (class_operator(tmp) && tmp->stat == GENERAL)
		{
			if (init_leaf(data, ft_strdup(tmp->string), tmp))
				return (throw_error(ERR_MAL));
			tmp = tmp->right;
		}
		else if (exclude(tmp))
			tmp = tmp->right;
		else
		{
			if (leaf(data, &tmp))
				return (throw_error(ERR_MAL));
		}
	}
	return (0);
}
