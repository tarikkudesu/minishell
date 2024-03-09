/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:05:56 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/09 18:50:29 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

t_env	*env_new(char *name, char *value)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->value = value;
	env->name = name;
	env->next = NULL;
	env->prev = NULL;
	return (env);
}

void	env_add_back(t_env **linked, t_env *node)
{
	t_env	*tmp;

	if (!linked || !node)
		return ;
	if (!*linked)
		*linked = node;
	else
	{
		tmp = *linked;
		while (tmp->next)
			tmp = tmp->next;
		node->prev = tmp;
		tmp->next = node;
	}
}

void	env_clear(t_env **env)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp)
	{
		*env = (*env)->next;
		(free(tmp->name), free(tmp->value), free(tmp));
		tmp = *env;
	}
}
