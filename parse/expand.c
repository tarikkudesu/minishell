/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:28:01 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/16 12:38:14 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	expand_variable(t_shell *data, t_tokens *token)
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
			return (1);
		free(token->string);
		token->string = string;
		return (0);
	}
	free(token->string);
	token->string = ft_strdup("");
	if (!token->string)
		return (1);
	return (0);
}

int	expand(t_shell *data, t_tokens *token)
{
	char	*string;
	char	*nbr;

	if (!ft_strcmp(token->string, "$"))
		return (0);
	else if (!ft_strncmp(token->string, "$?", 2))
	{
		string = token->string;
		nbr = ft_itoa(data->status);
		if (!nbr)
			return (1);
		token->string = ft_strjoin(nbr, token->string + 2);
		free(string);
		free(nbr);
		if (!token->string)
			return (1);
	}
	else
		return (expand_variable(data, token));
	return (0);
}
