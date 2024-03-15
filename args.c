/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:43:06 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/12 18:00:41 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// char	**get_args(t_tokens *branch)
// {
// 	char	*arg;
// 	char	*to_free;

// 	to_free = NULL;
// 	arg = NULL;
// 	while (branch)
// 	{
// 		if (branch->class == WORD)
// 		{
// 			to_free = arg;
// 			arg = ft_strjoin(branch->string, " ");
// 			if (!arg)
// 				return (NULL);
// 			if (to_free)
// 				free(to_free);
// 		}
// 		branch = branch->right;
// 	}
// 	return (ft_split(arg, ' '));
// }

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
