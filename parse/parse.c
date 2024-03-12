/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:32:45 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/12 10:32:46 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *leaf(t_shell *data, t_tokens **tmp, char *string)
{
	char		*to_free;

	if ((*tmp)->class == ENV && (*tmp)->stat != INQUOTE)
		expand(data, *tmp);
	to_free = string;
	string = ft_strjoin(string, (*tmp)->string);
	if (!string)
		return (NULL);
	free(to_free);
	return (string);
}

int init_leaf(t_shell *data, char *string, t_tokens *class)
{
	static int	i; // if there is no use of this variable remove it, ask otman
	t_tokens    *token;

	token = tokennew(string);
	if (!token)
		return (1);
	token->index = ++i;
	if (class->stat == GENERAL)
		token->class = class->class;
	else
		token->class = WORD;
	tokenadd_back(&data->tree, token);
	return (0);
}

void	inquote(t_shell *data, t_tokens **tmp)
{
	char		*string;
	t_tokens	*class;

	if ((*tmp)->class == ENV && (*tmp)->stat != INQUOTE)
		expand(data, *tmp);
	class = *tmp;
	string = ft_strdup((*tmp)->string);
	if (!string)
		return ;
	*tmp = (*tmp)->right;
	while (*tmp)
	{
		if (skip(*tmp))
			*tmp = (*tmp)->right;
		else if (keep(*tmp))
		{
			string = leaf(data, tmp, string);
			*tmp = (*tmp)->right;
		}
		else
			break ;
	}
	init_leaf(data, string, class);
}

int pars(t_shell *data)
{
	int			i;
	t_tokens    *tmp;

	i = 0;
	tmp = data->tokens;
	while (tmp)
	{
		if (add(tmp))
		{
			inquote(data, &tmp);
			i++;
		}
		else
			tmp = tmp->right;
	}
	data->number_of_commands = i;
	return (0);
}
