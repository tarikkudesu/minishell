/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 23:22:07 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/06 23:54:22 by ooulcaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"

void	unset(t_env **env, char *variable) //t_tokens *token instead of char *to_add
{											// to handle unset multiple varriable
	t_env	*node;
	t_env	*to_rm;

	node = *env;
	while (node)
	{
		if (!ft_strcmp(node->environ, variable))
		{
			to_rm = node;
			if (node->prev)
				node->prev->next = node->next;
			else
				(*env) = (*env)->next;
			free(to_rm);
			to_rm = NULL;
			break ;
		}
		node = node->next;
	}
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