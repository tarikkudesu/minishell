/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:48:45 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/10 11:07:02 by tamehri          ###   ########.fr       */
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
	return (free(name), 0);
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
		return (ft_putendl_fd(ERR_MAL, 2), 0);
	return (expansion_value_3(data->env_list, name));
}

int	expansion_value_1(t_shell *data, char *str, int *i)
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
