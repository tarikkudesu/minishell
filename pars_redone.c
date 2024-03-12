#include "includes/minishell.h"

void	expand(t_shell *data, t_tokens *token)
{
	char	*string;
	t_env	*env;

	env = data->env_list;
	while (env)
	{
		if (!ft_strcmp(token->string + 1, env->name))
			break ;
		env = env->next;
	}
	if (env)
	{
		string = ft_strdup(env->value);
		if (!string)
			return ;
		free(token->string);
		token->string = string;
		return ;
	}
	free(token->string);
	token->string = ft_strdup("");
}

int	add(t_tokens *token)
{
	if (token->type == RE_WORD)
		return (1);
	else if (token->stat == GENERAL)
	{
		if (token->type != WHITESPACE && token->type != QUOTE && token->type != DQUOTE)
			return (1);
	}
	else if (token->stat != GENERAL)
	{
		if (token->type != QUOTE && token->type != DQUOTE)
			return (1);
	}
	return (0);
}

int	skip(t_tokens *token)
{
	if (token->type == QUOTE || token->type == DQUOTE)
		return (1);
	return (0);
}

int	keep(t_tokens *token)
{
	if (token->type == RE_WORD || token->type == ENV)
		return (1);
	else if (token->stat != GENERAL)
		return (1);
	return (0);
}

void	inquote(t_shell *data, t_tokens **tmp)
{
	char		*to_free;
	char		*string;
	t_tokens	*token;

	if ((*tmp)->type == ENV && (*tmp)->stat != INQUOTE)
		expand(data, *tmp);
	string = ft_strdup((*tmp)->string);
	if (!string)
		return ;
	*tmp = (*tmp)->right;
	if (*tmp)
	{
		while (*tmp)
		{
			puts((*tmp)->string);
			if (skip(*tmp))
				*tmp = (*tmp)->right;
			else if (keep(*tmp))
			{
				if ((*tmp)->type == ENV && (*tmp)->stat != INQUOTE)
					expand(data, *tmp);
				to_free = string;
				string = ft_strjoin(string, (*tmp)->string);
				free(to_free);
				*tmp = (*tmp)->right;
			}
			else
				break ;
			usleep(50000);
		}
	}
	token = tokennew(string);
	if (!token)
		return ;
	tokenadd_back(&data->token, token);
}

int pars_redone(t_shell *data)
{
	t_tokens    *tmp;

	tmp = data->cherry;
	while (tmp)
	{
		if (add(tmp))
			inquote(data, &tmp);
		else
			tmp = tmp->right;
	}
	return (1);
}
