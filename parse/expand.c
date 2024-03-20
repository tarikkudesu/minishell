/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:28:01 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/20 17:46:45 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	expand_variable(t_env *env, t_tokens *token, int t)
{
	char	*string;

	if (t)
	{
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
				return (1);
			(free(token->string), token->string = string);
			return (0);
		}
	}
	(free(token->string), token->string = ft_strdup(""));
	if (!token->string)
		return (1);
	return (0);
}

int	expand(t_shell *data, t_tokens *token)
{
	char	*string;
	char	*nbr;

	if (token->string[0] == '$' && \
	(token->string[1] == '\'' || token->string[1] == '\''))
		return (expand_variable(data->env_list, token, 0));
	else if (token->string[0] == '$')
		return (0);
	else if (!ft_strncmp(token->string, "$?", 2))
	{
		string = token->string;
		nbr = ft_itoa(data->status);
		if (!nbr)
			return (1);
		token->string = ft_strjoin(nbr, token->string + 2);
		(free(string), free(nbr));
		if (!token->string)
			return (1);
	}
	else
		return (expand_variable(data->env_list, token, 1));
	return (0);
}
