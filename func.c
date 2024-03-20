/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:30:42 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/20 19:39:48 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"


void d(int i) {
    while (i-- >= 0)
        printf("\t");
}

void    print_branch(t_tokens *cmd, int i) {
    while (cmd) {
        d(i);
        printf("[\033[32m%s\033[0m] [%c] [%c]\n", cmd->string, cmd->class, cmd->stat);
        cmd = cmd->right;
    }
}

void    print_tree(t_tokens *tree)
{
    int i = 0;
	while (tree)
	{
		print_branch(tree, i);
		tree = tree->left;
		i++;
	}
}

void c() {system("lsof -c minishell > fildes");}
void f() {system("leaks minishell");}

void s() {
	for (int i = 0; i < FD_SETSIZE; i++) {
		if (fcntl(i, F_GETFD) != -1) {
			dprintf(2, "%d : %d is open\n", getpid(), i);
		}
	}
}

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
