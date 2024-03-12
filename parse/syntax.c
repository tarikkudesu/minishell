/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 20:28:15 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/10 13:32:20 by tamehri          ###   ########.fr       */
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

int	check_syntax(t_shell *data) // this doesn't work my friend
{
	t_tokens	*tmp;
	t_tokens	*previous;

	tmp = data->tree->right;
	previous = data->tree;
	while (tmp)
	{
		if (class_operator(tmp) && class_operator(previous))
		{
			if (previous->class != PIPE)
			{
				printf("parse error\n");
				data->status = 258;
				return (1);
			}
		}
		previous = tmp;
		tmp = tmp->right;
	}
	if (class_operator(previous))
	{
		printf("parse error\n");
		data->status = 258;
		return (1);
	}
	return (0);
}
