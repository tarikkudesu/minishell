/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 22:50:34 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/17 13:55:30 by tamehri          ###   ########.fr       */
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

int	get_env(t_shell *data, char **env)
{
	int		i;
	char	*name;
	char	*value;
	char	*start;
	t_env	*node;

	i = -1;
	while (env[++i])
	{
		start = ft_strchr(env[i], '=');
		name = ft_substr(env[i], 0, (start - env[i]));
		if (!name)
			return (1);
		value = ft_strdup(start + 1);
		if (!value)
			return (free(name), 1);
		node = env_new(name, value);
		if (!node)
			return (free(name), free(value), 1);
		env_add_back(&data->env_list, node);
	}
	return (0);
}
