/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:05:03 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/15 15:22:58 by ooulcaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*copy_list(t_env *list)
{
	t_env	*env;
	t_env	*node;
	char	*name;
	char	*value;

	env = NULL;
	while (list)
	{
		if (list->name)
			name = ft_strdup(list->name);
		if (list->value)
			value = ft_strdup(list->value);
		node = env_new(name, value);
		if (!node)
			return (perror("ERROR_NEW_NODE_EXPORT"), NULL);
		env_add_back(&env, node);
		list = list->next;
		value = NULL;
	}
	return (env);
}

void	sort_list(t_env *env)
{
	t_env	*i;
	t_env	*j;
	char	*help;

	i = env;
	while (i->next)
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

void	new_var(t_env *env, char **splited)
{
	t_env	*tmp;
	t_env	*node;

	tmp = env;
	while (tmp->next && ft_strcmp(tmp->name, splited[0]))
		tmp = tmp->next;
	if (!ft_strcmp(tmp->name, splited[0]))
		(free(tmp->value), free(splited[0]), tmp->value = splited[1]);
	else
	{
		node = env_new(splited[0], splited[1]);
		if (!node)
			return (perror("ERROR_LSTNEW_EXPORT"));
		env_add_back(&env, node);
	}
}

void	append(t_env *env, char **splited)
{
	t_env	*node;
	char	*join;
	int		strlen;

	strlen = ft_strlen(splited[0]) - 1;
	while (env->next && ft_strncmp(splited[0], env->name, strlen))
		env = env->next;
	if (!ft_strncmp(splited[0], env->name, strlen))
	{
		join = ft_strjoin(env->value, splited[1]);
		if (!join)
			ft_throw("ERROR_SUBSTR_APPEND<<<", 1);
		(free(env->value), env->value = NULL);
		env->value = join;
		free_2d_char(splited);
	}
	else
	{
		node = env_new(ft_substr(splited[0], 0, strlen), splited[1]);
		env->next = node;
		(free(splited[0]), free(splited));
	}
}

void	ft_export(t_shell *data, t_env **env, char **to_add, int add)
{
	char	**splited;
	t_env	*tmp;
	int		i;

	i = -1;
	while (add && to_add[++i])
	{
		splited = ft_split(to_add[i], '=');
		if (!splited)
			return (data->status = 1, perror("ERROR_SPLIT_EXPORT"));
		if (splited[0][ft_strlen(splited[0]) - 1] == '+')
			append(*env, splited);
		else
			(new_var(*env, splited), free(splited));
	}
	if (add)
		data->env = env_to_array(data->env_list);
	else
	{
		tmp = copy_list(*env);
		(sort_list(tmp), env_clear(&tmp));
	}
	data->status = 0;
	if (data->number_of_commands > 1)
		exit(0);
}
