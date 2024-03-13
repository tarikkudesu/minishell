/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:32:45 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/12 17:09:48 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*leaf(t_shell *data, t_tokens **tmp, char *string)
{
	char		*to_free;

	if ((*tmp)->class == ENV && (*tmp)->stat != INQUOTE)
		expand(data, *tmp);
	to_free = string;
	string = ft_strjoin(string, (*tmp)->string);
	if (!string)
		return (free(to_free), ft_putendl_fd(ERR_MAL, 2), NULL);
	free(to_free);
	return (string);
}

int	sub_leafs(t_shell *data, char *string, char **arr, t_tokens *class)
{
	int	i;

	i = 0;
	puts("hi there");
	if (!arr)
		return (free(string), ft_putendl_fd(ERR_MAL, 2), 1);
	while (*(arr + i))
	{
		if (init_leaf(data, *(arr + i), class, 0))
			return (free_2d(arr), ft_putendl_fd(ERR_MAL, 2), 1);
		i++;
	}
	free(arr);
	free(string);
	return (0);
}

int	init_leaf(t_shell *data, char *string, t_tokens *class, int split)
{
	t_tokens	*token;

	if (split)
		return (sub_leafs(data, string, ft_split(string, ' '), class));
	token = tokennew(string);
	if (!token)
		return (ft_putendl_fd(ERR_MAL, 2), 1);
	if (class->stat == GENERAL)
		token->class = class->class;
	else
		token->class = WORD;
	tokenadd_back(&data->tree, token);
	return (0);
}

int	inquote(t_shell *data, t_tokens **tmp, char **string, int split)
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
			if ((*tmp)->class == ENV && (*tmp)->stat == GENERAL)
				split = 1;
			*string = leaf(data, tmp, *string);
			if (!*string)
				return (1);
			*tmp = (*tmp)->right;
		}
		else
			break ;
	}
	return (init_leaf(data, *string, class, split));
}

int	pars(t_shell *data)
{
	t_tokens	*tmp;
	int			split;
	char		*string;

	split = 0;
	tmp = data->tokens;
	while (tmp)
	{
		if (add(tmp))
		{
			if (tmp->class == ENV && tmp->stat != INQUOTE)
			{
				expand(data, tmp);
				if (tmp->stat == GENERAL)
					split = 1;
				orttmp->class = WORD;
			}
			string = ft_strdup(tmp->string);
			if (!string)
				return (ft_putendl_fd(ERR_MAL, 2), 1);
			if (inquote(data, &tmp, &string, split))
				return (1);
		}
		else
			tmp = tmp->right;
	}
	return (0);
}
