/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:32:45 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/15 15:41:24 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*join_tokens(t_shell *data, t_tokens **tmp, char *string)
{
	char		*to_free;

	if ((*tmp)->class == ENV && (*tmp)->stat != INQUOTE)
		if (expand(data, *tmp))
			return (NULL);
	to_free = string;
	string = ft_strjoin(string, (*tmp)->string);
	if (!string)
		return (free(to_free), ft_putendl_fd(ERR_MAL, 2), NULL);
	free(to_free);
	return (string);
}

int	init_leaf(t_shell *data, char *string, t_tokens *class)
{
	t_tokens	*token;

	token = tokennew(string);
	if (!token)
		return (free(string), throw_error(ERR_MAL));
	if (class->stat == GENERAL)
		token->class = class->class;
	else
		token->class = WORD;
	tokenadd_back(&data->tree, token);
	return (0);
}

int	leaf(t_shell *data, t_tokens **tmp, char **string)
{
	t_tokens	*class;

	class = *tmp;
	*tmp = (*tmp)->right;
	while (*tmp)
	{
		if (skip(*tmp))
			*tmp = (*tmp)->right;
		else if (keep(*tmp))
		{
			*string = join_tokens(data, tmp, *string);
			if (!*string)
				return (1);
			*tmp = (*tmp)->right;
		}
		else
			break ;
	}
	return (init_leaf(data, *string, class));
}

int	pars(t_shell *data)
{
	t_tokens	*tmp;
	char		*string;

	tmp = data->tokens;
	while (tmp)
	{
		if (add(tmp))
		{
			if (tmp->class == ENV && tmp->stat != INQUOTE)
				if (expand(data, tmp))
					return (1);
			string = ft_strdup(tmp->string);
			if (!string)
				return (ft_putendl_fd(ERR_MAL, 2), 1);
			if (leaf(data, &tmp, &string))
				return (1);
		}
		else
			tmp = tmp->right;
	}
	return (0);
}
