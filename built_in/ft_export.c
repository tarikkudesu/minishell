/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:05:03 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/23 11:52:36 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sort_list(t_env *env)
{
	t_env	*i;
	t_env	*j;
	char	*help;

	i = env;
	while (i && i->next)
	{
		j = i->next;
		while (j)
		{
			if (ft_strcmp(i->name, j->name) > 0)
			{
				help = i->name;
				i->name = j->name;
				j->name = help;
				help = i->value;
				i->value = j->value;
				j->value = help;
			}
			j = j->next;
		}
		i = i->next;
	}
	print(env);
}

t_env	*copy_list(t_env *list)
{
	t_env	*env;
	t_env	*node;
	char	*name;
	char	*value;

	env = NULL;
	while (list)
	{
		name = NULL;
		value = NULL;
		if (list->name)
			name = ft_strdup(list->name);
		if (list->value)
			value = ft_strdup(list->value);
		node = env_new(name, value);
		if (!node)
			return (free(name), free(value), perror(ERR_MAL), NULL);
		env_add_back(&env, node);
		list = list->next;
	}
	return (env);
}

void	ft_export(t_shell *data, t_env **env, char **to_add, int add)
{
	t_env	*tmp;

	if (add)
		add_export(data, to_add);
	else
	{
		tmp = copy_list(*env);
		(sort_list(tmp), env_clear(&tmp));
		data->status = 0;
	}
	if (data->cmd_nbr > 1)
		exit(0);
}
