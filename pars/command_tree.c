/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:45:41 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/07 15:41:31 by ooulcaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void d(int i) {
    while (i-- >= 0)
        printf("\t");
}

void    print_branch(t_tokens *cmd, int i) {
    while (cmd) {
        d(i);
        printf("%s\n", cmd->string);
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

void    command_tree(t_shell *data)
{
    int            i;
    t_tokens    *tmp;
    t_tokens    *pipe;
    t_tokens    *cmd_tree;

    i = 0;
    tmp = data->token;
    cmd_tree = data->token;
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
    data->number_of_commands = i + 1;
    print_tree(data->token);
}