/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:49:59 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/03 15:29:48 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tokens	*tokennew(char *content)
{
	t_tokens	*head;

	head = (t_tokens *)malloc(sizeof(t_tokens));
	if (!head)
		return (NULL);
	head->token = content;
	head->class = WORD;
	head->next = NULL;
	return (head);
}
void	tokenadd_back(t_tokens **lst, t_tokens *new)
{
	t_tokens	*temp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	if (!new)
		return ;
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}
void	tokenclear(t_tokens **lst)
{
	t_tokens	*temp;

	if (!*lst)
		return ;
	temp = *lst;
	while (lst && *lst)
	{
		temp = temp->next;
		free(*lst);
		*lst = temp;
	}
}
