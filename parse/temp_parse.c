#include "../includes/minishell.h"


int	leaf(t_shell *data, t_tokens **tmp)
{
	t_tokens	*class;
	char		*string;

	class = *tmp;
	string = NULL;
	while (*tmp && !exclude(*tmp))
	{
		if (skip(*tmp))
			*tmp = (*tmp)->right;
		else
		{
			string = join_tokens(tmp, string);
			if (!string)
				return (throw_error(ERR_MAL));
			*tmp = (*tmp)->right;
		}
	}
	return (init_leaf(data, string, class));
}

int	pars(t_shell *data)
{
	t_tokens	*tmp;

	tmp = data->tokens;
	while (tmp)
	{
		if (class_operator(tmp) && tmp->stat == GENERAL)
		{
			if (init_leaf(data, ft_strdup(tmp->string), tmp))
				return (throw_error(ERR_MAL));
			tmp = tmp->right;
		}
		else
			if (leaf(data, &tmp))
				return (1);
	}
	return (0);
}