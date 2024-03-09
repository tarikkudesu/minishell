/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 20:28:15 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/06 15:50:24 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_operatr(t_tokens *token)
{
	if (token->class == INPUT_RED || token->class == OUTPUT_RED)
		return (1);
	if (token->class == HEREDOC || token->class == APPEND)
		return (1);
	if (token->class == PIPE)
		return (1);
	return (0);
}

void	check_syntax(t_shell *data)
{
	t_tokens	*tmp;
	t_tokens	*previous;

	tmp = data->token->right;
	previous = data->token;
	while (tmp)
	{
		if (is_operatr(tmp) && is_operatr(previous) && previous->class != PIPE)
		{
			printf("parse error near '%s'\n", tmp->string);
			return ;
		}
		previous = tmp;
		tmp = tmp->right;
	}
}
