/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:45:41 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/19 17:27:31 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	command_tree(t_shell *data)
{
	int			i;
	t_tokens	*tmp;
	t_tokens	*pipe;
	t_tokens	*cmd_tree;

	i = 0;
	tmp = data->tree;
	cmd_tree = data->tree;
	while (tmp->right)
	{
		if (tmp->class == PIPE)
		{
			cmd_tree->left = tmp->right;
			cmd_tree = cmd_tree->left;
			pipe = tmp->right;
			tmp->right = NULL;
			tmp = pipe;
			i++;
		}
		if (tmp->right)
			tmp = tmp->right;
	}
	data->cmd_nbr = i + 1;
}
