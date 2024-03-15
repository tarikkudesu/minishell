/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:30:42 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/15 14:31:05 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void fonction_mli7a(t_shell *data)
{
	t_tokens	*token;
	token = data->tokens;

	while (token)
	{
		printf("\t\t[\033[1;32m\t%s\t\033[0m]\ttype : \t|\033[1;33m%c\033[0m|\t stat : |\033[1;34m%c\033[0m|\n", token->string, token->class, token->stat);
		token = token->right;
	}
	printf("------------------------------------------------------------\n");
	token = data->tree;
	while (token)
	{
		printf("\t\t[\033[1;32m%s\033[0m]class : \t|\033[1;33m%c\033[0m|\t stat : |\033[1;34m%c\033[0m|\n", token->string, token->class, token->stat);
		token = token->right;
	}
}
