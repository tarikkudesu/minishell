/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minifun.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:57:51 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/07 00:21:39 by ooulcaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	print(t_env **env)
// {
// 	t_env	*tmp;

// 	tmp = *env;
// 	while (tmp)
// 	{
// 		ft_putendl_fd(tmp->environ, 1);
// 		tmp = tmp->next;
// 	}
// }

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (*(s1 + i) && *(s1 + i) && *(s1 + i) == *(s2 + i))
		i++;
	return (*(s1 + i) - *(s2 + i));
}

int	is_operator(int c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	is_space(int c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else if (c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

int	bunny_ears(char **s, char c)
{
	(*s)++;
	while (**s && **s != c)
		(*s)++;
	return (1);
}
void	assign(int *nbr, int add)
{
	(*nbr) = add;
}
