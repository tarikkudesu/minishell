#include "includes/minishell.h"

void	expand(t_shell *data, t_tokens *token)
{
	char	*string;
	t_env	*env;

	env = data->env_list;
	while (env)
	{
		if (!ft_strcmp(token->string, env->name))
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

int	xclass(t_type type)
{
	if (type == RE_PIPE || type == IN_RED || type == OUT_RED \
		|| type == RE_HEREDOC || type == RE_APPEND)
		return (1);
	return (0);
}

int	stop(t_tokens *token)
{
	if (!token)
		return (1);
	if (token->stat == GENERAL && token->type != RE_WORD)
		return (1);
	return (0);
}

int	add2(t_tokens *token)
{
	if (token->stat == GENERAL && token->type != WHITESPACE && token->type != DQUOTE && token->type != QUOTE)
		return (1);
	return (0);
}

int	add(t_tokens *token)
{
	if (token->stat == GENERAL && token->type == RE_WORD)
		return (1);
	else if (token->stat != GENERAL && token->type != DQUOTE && token->type != QUOTE)
		return (1);
	return (0);
}

void	inquote(t_shell *data, t_tokens **tmp)
{
	char		*string;
	char		*to_free;
	t_tokens	*token;

	string = ft_strdup((*tmp)->string);
	if (!string)
		return ;
	printf("|%s|\n", string);
	*tmp = (*tmp)->right;
	while (!stop(*tmp))
	{
		puts("----");
		if ((*tmp)->type == ENV && (*tmp)->stat != INQUOTE)
			expand(data, (*tmp));
		if (add(*tmp))
		{
			to_free = string;
			string = ft_strjoin(string, (*tmp)->string);
			free(to_free);
		}
		*tmp = (*tmp)->right;
	}
	token = tokennew(string);
	if (!token)
	{
		free(string);
		return ;
	}
	tokenadd_back(&data->token, token);
}

int pars_redone(t_shell *data)
{
	t_tokens    *tmp;

	tmp = data->cherry;
	while (tmp)
	{
		if (add2(tmp))
			inquote(data, &tmp);
		else
			tmp = tmp->right;
	}
	return (1);
}
