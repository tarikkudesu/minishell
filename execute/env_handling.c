/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 22:50:34 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/19 18:29:42 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*env_join(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*res;

	if (!s1 || !s2)
		return (0);
	res = malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (!res)
		return (NULL);
	i = -1;
	while (*(s1 + ++i))
		*(res + i) = *(s1 + i);
	*(res + i++) = '=';
	j = 0;
	while (*(s2 + j))
		*(res + i++) = *(s2 + j++);
	*(res + i) = '\0';
	return (res);
}

char	**env_to_array(t_env *env_list)
{
	int		i;
	int		size;
	char	**env;

	size = env_size(env_list);
	env = malloc(sizeof(char *) * (size + 1));
	if (!env)
		return (NULL);
	i = 0;
	if (env_list)
	{
		while (i < size)
		{
			*(env + i) = env_join(env_list->name, env_list->value);
			if (!*(env + i))
				return (free_2d_char(env), NULL);
			env_list = env_list->next;
			i++;
		}
	}
	*(env + i) = NULL;
	return (env);
}

int	insert_env_node(t_shell *data, char *name, char *env)
{
	t_env	*node;
	char	*value;

	if (!ft_strcmp(name, "SHLVL"))
		value = ft_itoa(ft_atoi(ft_strchr(env, '=') + 1) + 1);
	else if (!ft_strcmp(name, "PWD"))
		value = ft_strdup(data->pwd);
	else
		value = ft_strdup(ft_strchr(env, '=') + 1);
	if (!value)
		return (free(name), 1);
	node = env_new(name, value);
	if (!node)
		return (free(name), free(value), 1);
	env_add_back(&data->env_list, node);
	return (0);
}

int	get_env(t_shell *data, char **env)
{
	int		i;
	char	*name;

	i = -1;
	while (env[++i])
	{
		name = ft_substr(env[i], 0, (ft_strchr(env[i], '=') - env[i]));
		if (!name)
			return (1);
		if (ft_strcmp(name, "OLDPWD"))
		{
			if (insert_env_node(data, name, env[i]))
				return (1);
		}
		else
			free(name);
	}
	return (0);
}
