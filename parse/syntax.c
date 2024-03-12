/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 20:28:15 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/12 17:48:54 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	class_operator(t_tokens *token)
{
	if (token->class == IN_RED || token->class == OUT_RED \
		|| token->class == HEREDOC || token->class == APPEND \
		|| token->class == PIPE)
		return (1);
	return (0);
}

int	pars_error(t_shell *data)
{
	printf("pars error\n");
	data->status = 258;
	return (1);
}

int	check_syntax(t_shell *data)
{
	t_tokens	*tmp;
	t_tokens	*previous;

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
	return (0);
}
