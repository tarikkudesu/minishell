
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
