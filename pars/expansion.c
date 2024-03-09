/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:48:45 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/04 17:50:29 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	expansion_value_3(t_env *env, char *name)
{
	while (env)
	{
		if (!ft_strcmp(env->name, name))
			return (free(name), ft_strlen(env->value));
		env = env->next;
	}
	return (0);
}

int	expansion_value_2(t_shell *data, char *str, int *i)
{
	int		len;
	char	*name;

	len = 0;
	while (*(str + len + 1) && ft_isalnum(*(str + len + 1)))
		len++;
	(*i) += len + 1;
	if (!len)
		return (1);
	name = ft_substr(str + 1, 0, len);
	if (!name)
		return (0);
	return (expansion_value_3(data->env_list, name));
}

int	expansion_value_1(t_shell *data, char *str, int *i) //changed
{
	int		len;
	char	*nbr;

	len = 0;
	if (ft_isdigit(*(str + 1)))
	{
		(*i) += 2;
		return (0);
	}
	else if (*(str + 1) == '?')
	{
		nbr = ft_itoa(data->status);
		if (!nbr)
			return (0);
		len = ft_strlen(nbr);
		(*i) += 2;
		return (free(nbr), len);
	}
	return (expansion_value_2(data, str, i));
}

// void	expand(char **s, char *tmp, int i[3]) // changed
// {
// 	int		x;
// 	int		len;
// 	char	*var;
// 	char	*val;

// 	x = 0;
// 	len = 0;
// 	while (*(tmp + i[0] + len + 1) && ft_isalnum(*(tmp + i[0] + len + 1)))
// 		len++;
// 	((!len) && (*(*s + i[1]) = *(tmp + i[0])) && (i[0] += 1) && (i[1] += 1));
// 	if (!len)
// 		return ;
// 	var = ft_substr(tmp, i[0] + 1, len);
// 	if (!var)
// 		return ;
// 	i[0] += len + 1;
// 	val = getenv(var);
// 	if (!val)
// 		return ;
// 	while (*(val + x))
// 	{
// 		*(*s + i[1]) = *(val + x);
// 		i[1] += 1;
// 		x++;
// 	}
// }
