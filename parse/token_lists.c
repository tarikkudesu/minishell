/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:49:59 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/20 15:50:49 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tokens	*tokennew(char *content)
{
	t_tokens	*head;

	head = (t_tokens *)malloc(sizeof(t_tokens));
	if (!head)
		return (NULL);
	head->string = content;
	head->class = DEFAULT;
	head->stat = GENERAL;
	head->right = NULL;
	head->left = NULL;
	return (head);
}

void	tokenadd_back(t_tokens **lst, t_tokens *new)
{
	t_tokens	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->right)
		temp = temp->right;
	temp->right = new;
}

int	tokensize(t_tokens *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = 1;
	while (lst->right)
	{
		i++;
		lst = lst->right;
	}
	return (i);
}

void	tokenclear(t_tokens **branch)
{
	t_tokens	*tmp;

	if (!branch || !*branch)
		return ;
	tmp = *branch;
	while (branch && *branch)
	{
		free(tmp->string);
		tmp->string = NULL;
		tmp = tmp->right;
		free(*branch);
		*branch = tmp;
	}
}

void	clear_command_tree(t_tokens **tree)
{
	t_tokens	*tmp;

	if (!tree || !*tree)
		return ;
	tmp = *tree;
	while (tree && *tree)
	{
		tmp = tmp->left;
		tokenclear(tree);
		*tree = tmp;
	}
}
