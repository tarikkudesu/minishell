/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 23:22:07 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/10 23:46:24 by ooulcaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_unset(t_env **env, char **vars)
{
	t_env	*node;
	t_env	*to_rm;
	int		i;

	node = *env;
	i = -1;
	while (vars[++i])
	{
		while (node)
		{
			if (!ft_strcmp(node->name, vars[i]))
			{
				to_rm = node;
				if (node->prev)
					node->prev->next = node->next;
				else
					(*env) = (*env)->next;
				(free(to_rm->value), free(to_rm->name), free(to_rm));
				break ;
			}
			node = node->next;
		}
		node = *env;
	}
	exit(0);
}

// int	main()
// {
// 	t_env	*test;
// 	t_env	*tmp;
// 	char	*dup;
// 	int		i;

// 	test = NULL;
// 	char prototype[5] = "HOME";
// 	i = 0;
// 	while (i++ < 10)
// 	{
// 		prototype[3]++;
// 		dup = ft_strdup(prototype);
// 		env_add_back(&test, env_new(dup));
// 	}
// 	unset(&test, "HOMF");
// 	tmp = test;
// 	while (tmp)
// 		(puts(tmp->environ), tmp = tmp->next);
// }
