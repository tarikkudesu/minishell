/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:35:59 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/06 15:50:16 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	this function will set the class of each token
	each member of the list is a token with a spesific class,
*/
void	token_class(t_tokens *token)
{
	t_tokens	*tmp;

	tmp = token;
	while (tmp)
	{
		if (!ft_strcmp(tmp->string, "|"))
			tmp->class = PIPE;
		else if (!ft_strcmp(tmp->string, "<"))
			tmp->class = INPUT_RED;
		else if (!ft_strcmp(tmp->string, ">"))
			tmp->class = OUTPUT_RED;
		else if (!ft_strcmp(tmp->string, "<<"))
			tmp->class = HEREDOC;
		else if (!ft_strcmp(tmp->string, ">>"))
			tmp->class = APPEND;
		tmp = tmp->right;
	}
}
