/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:49:59 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/07 19:30:54 by ooulcaid         ###   ########.fr       */
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
	head->index = 1;
	head->class = WORD;
	head->right = NULL;
	head->left = NULL;
	return (head);
}

void	tokenadd_back(t_tokens **lst, t_tokens *new)
{
	t_tokens	*temp;

	// puts("here");
	if (!lst)
		return ;
	if (!new)
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

void	tokenclear(t_tokens **lst)
{
	t_tokens	*temp;

	if (!*lst)
		return ;
	temp = *lst;
	while (lst && *lst)
	{
		free(temp->string);
		temp = temp->right;
		free(*lst);
		*lst = temp;
	}
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
