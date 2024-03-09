/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_environement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 23:18:12 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/09 11:21:41 by ooulcaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*get_env(char **env)
{
	t_env	*list;
	t_env	*node;
	int		i;
	char	*content;

	i = 0;
	list = NULL;
	while (env[i])
	{
		content = ft_strdup(env[i]);
		if (!content)
			ft_throw("ERROR_STRDUP_GET_ENV");
		node = env_new(content, NULL);
		if (!node)
			ft_throw("ERROR_NEW_NODE_GET_ENV");
		env_add_back(&list, node);
		i++;
	}
	return (list);
}
