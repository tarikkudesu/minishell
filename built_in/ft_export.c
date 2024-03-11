/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:39:06 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/10 23:46:07 by ooulcaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	swap(char **s1, char **s2)
{
	char	*help;

	help = *s1;
	*s1 = *s2;
	*s2 = help;
}

t_env	*sort_list(t_env *env)
{
	t_env	*i;
	t_env	*j;

	i = env;
	while (i->next)
	{
		j = i->next;
		while (j)
		{
			if (ft_strcmp(i->name, j->name) > 0)
				(swap(&(i->name), &(j->name)), swap(&(j->value), &(j->value)));
			j = j->next;
		}
		i = i->next;
	}
	return (env);
}

void	ft_export(t_env **env, char **to_add, int add)
{
	t_env	*node;
	t_env	*tmp;
	int		i;

	tmp = *env;
	if (add)
	{
		while (tmp->next)
			tmp = tmp->next;
		i = -1;
		while (to_add[++i])
		{
			node = env_new(to_add[i], NULL);
			if (!node)
				ft_throw("ERROR_LSTNEW_EXPORT", 1);
			env_add_back(env, node);
		}
		return ;
	}
	tmp = *env;
	print(sort_list(tmp));
	exit(0);
}

// int	main(int ac, char **av, char **env)
// {
// 	char *str;
// 	int	i;
// 	i = 0;
// 		*list_env = NULL;
// 		*node;
// 	while (env[i])
// 	{
// 		str = ft_strdup(env[i]);
// 		if (!str)
// 			ft_throw("EXPORT_STRDUP_ERROR");
// 		node = tokennew(str);
// 		if (!node)
// 			ft_throw("hna");
// 		tokenadd_back(&list_env, node);
// 		i++;
// 	}
// 	export(&list_env, NULL, 0);
// 	tokenclear(&list_env);
// }