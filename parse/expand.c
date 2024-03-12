/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:28:01 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/12 13:28:02 by tamehri          ###   ########.fr       */
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
		token->string = ft_strjoin(ft_itoa(data->status), token->string + 2);
		free(string);
		if (!token->string)
			return ;
	}
	else
		expand_variable(data, token);
}
