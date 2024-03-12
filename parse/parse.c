/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:32:45 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/12 10:32:46 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand_variable(t_shell *data, t_tokens *token)
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

void	expand(t_shell *data, t_tokens *token)
{
	char	*string;

	if (!ft_strcmp(token->string, "$"))
		return ;
	else if (ft_strcmp(token->string, "$?"))
	{
		string = token->string;
		token->string = ft_itoa(data->status);
		free(string);
		if (!token->string)
			return ;
	}
	else
		expnad_varibale(data, token);
}

char    *leaf(t_shell *data, t_tokens **tmp, char *string)
{
	char		*to_free;

	if ((*tmp)->class == ENV && (*tmp)->stat != INQUOTE)
		expand(data, *tmp);
	to_free = string;
	string = ft_strjoin(string, (*tmp)->string);
	if (!string)
		return (NULL);
	free(to_free);
	return (string);
}

int init_leaf(t_shell *data, char *string, t_tokens *class)
{
	static int	i; // if there is no use of this variable remove it, ask otman
	t_tokens    *token;

	token = tokennew(string);
	if (!token)
		return (1);
	token->index = ++i;
	if (class->stat == GENERAL)
		token->class = class->class;
	else
		token->class = WORD;
	tokenadd_back(&data->tree, token);
	return (0);
}

void	inquote(t_shell *data, t_tokens **tmp)
{
	static int	i;
	char		*string;
	t_tokens	*class;

	if ((*tmp)->class == ENV && (*tmp)->stat != INQUOTE)
		expand(data, *tmp);
	class = *tmp;
	string = ft_strdup((*tmp)->string);
	if (!string)
		return ;
	*tmp = (*tmp)->right;
	while (*tmp)
	{
		if (skip(*tmp))
			*tmp = (*tmp)->right;
		else if (keep(*tmp))
		{
			string = leaf(data, tmp, string);
			*tmp = (*tmp)->right;
		}
		else
			break ;
	}
	data->number_of_commands = ++i;
	init_leaf(data, string, class);
}

int pars(t_shell *data)
{
	t_tokens    *tmp;

	tmp = data->tokens;
	while (tmp)
	{
		if (add(tmp))
			inquote(data, &tmp);
		else
			tmp = tmp->right;
	}
	return (0);
}
