/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:09:12 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/10 11:08:06 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	expand_3(t_env *env, char **s, char *name, int i[3])
{
	char	*tmp;

	tmp = NULL;
	while (env)
	{
		if (!ft_strcmp(env->name, name))
			break ;
		env = env->next;
	}
	if (env)
	{
		tmp = env->value;
		while (*tmp)
		{
			*(*s + i[1]) = *tmp;
			i[1]++;
			tmp++;
		}
	}
	free(name);
}

static void	expand_2(t_shell *data, char **s, char *tmp, int i[3])
{
	int		len;
	char	*name;

	len = 0;
	while (*(tmp + i[0] + len + 1) && ft_isalnum(*(tmp + i[0] + len + 1)))
		len++;
	if (!len)
	{
		*(*s + i[1]) = *(tmp + i[0]);
		(assign(i, i[0] + 1), assign(i + 1, i[1] + 1));
		return ;
	}
	name = ft_substr(tmp + i[0] + 1, 0, len);
	if (!name)
		return ;
	expand_3(data->env_list, s, name, i);
	i[0] += len + 1;
}

static void	expand_1(t_shell *data, char **s, char *tmp, int i[3])
{
	char	*nbr;
	int		j;

	j = 0;
	if (ft_isdigit(*(tmp + i[0] + 1)))
	{
		i[0] += 2;
		return ;
	}
	else if (*(tmp + i[0] + 1) == '?')
	{
		nbr = ft_itoa(data->status);
		if (!nbr)
			return ;
		while (*(nbr + j))
			*(*s + i[1]++) = *(nbr + j++);
		i[0] += 2;
		free(nbr);
	}
	else
		expand_2(data, s, tmp, i);
}

void	fill_token(t_shell *data, char **s, char *tmp, int i[3])
{
	if (*(tmp + i[0]) == '\"' || *(tmp + i[0]) == '\'')
	{
		(assign(i + 2, *(tmp + i[0])), assign(i, i[0] + 1));
		while (*(tmp + i[0]) && *(tmp + i[0]) != i[2])
		{
			if (*(tmp + i[0]) == '$' && i[2] == '\"')
				expand_1(data, s, tmp, i);
			else
			{
				*(*s + i[1]) = *(tmp + i[0]);
				(assign(i, i[0] + 1), assign(i + 1, i[1] + 1));
			}
		}
		i[0]++;
	}
	else if (*(tmp + i[0]) == '$')
	{
		expand_1(data, s, tmp, i);
	}
	else
	{
		*(*s + i[1]) = *(tmp + i[0]);
		(assign(i, i[0] + 1), assign(i + 1, i[1] + 1));
	}
}
