/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 20:28:15 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/05 13:50:15 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	here_document(t_shell *data)
{
	t_tokens	*tmp;

	tmp = data->tokens;
	while (tmp)
	{
		if (tmp->stat == GENERAL && tmp->class == HEREDOC)
		{
			if (heredoc(data, tmp->right->string, tmp->right->class))
				return (1);
		}
		tmp = tmp->right;
	}
	return (0);
}

int	pars_error(t_shell *data)
{
	ft_putendl_fd(ERR_SYNTAX, 2);
	data->status = 258;
	return (1);
}

int	syntax(t_shell *data)
{
	t_tokens	*tmp;
	t_tokens	*previous;

	if (tokensize(data->tree) == 0)
		return (1);
	tmp = data->tree->right;
	previous = data->tree;
	if (previous->class == PIPE)
		return (pars_error(data));
	while (tmp)
	{
		if (class_operator(tmp) && class_operator(previous))
			if (previous->class != PIPE)
				return (pars_error(data));
		if (previous->class == IN_RED || previous->class == OUT_RED \
			|| previous->class == HEREDOC || previous->class == APPEND)
			tmp->class = FILE_NAME;
		previous = tmp;
		tmp = tmp->right;
	}
	if (class_operator(previous))
		return (pars_error(data));
	return (here_document(data));
}
