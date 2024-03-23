/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:05:56 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/23 14:52:37 by ooulcaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "_"))
		{
			(ft_putstr_fd("declare -x ", 1), ft_putstr_fd(tmp->name, 1));
			if (tmp->value)
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(tmp->value, 1);
				ft_putstr_fd("\"", 1);
			}
			ft_putstr_fd("\n", 1);
		}
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
		if (tmp->value)
			free(tmp->value);
		if (tmp->name)
			free(tmp->name);
		free(tmp);
		tmp = *env;
	}
	*env = NULL;
}

int	env_size(t_env *env)
{
	int	i;

	if (!env)
		return (0);
	i = 1;
	while (env->next)
	{
		i++;
		env = env->next;
	}
	return (i);
}
