/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:52:27 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/20 16:54:17 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	new_var(t_env *env, char **splited)
{
	t_env	*tmp;
	t_env	*node;

	tmp = env;
	while (tmp->next && ft_strcmp(tmp->name, splited[0]))
		tmp = tmp->next;
	if (!ft_strcmp(tmp->name, splited[0]))
		(free(tmp->value), free(splited[0]), tmp->value = splited[1]);
	else
	{
		node = env_new(splited[0], splited[1]);
		if (!node)
			return (ft_putendl_fd(ERR_MAL, 2));
		env_add_back(&env, node);
	}
}

int	append(t_env *env, char **splited)
{
	t_env	*node;
	char	*join;
	int		strlen;

	strlen = ft_strlen(splited[0]) - 1;
	while (env->next && ft_strncmp(splited[0], env->name, strlen))
		env = env->next;
	if (!ft_strncmp(splited[0], env->name, strlen))
	{
		join = ft_strjoin(env->value, splited[1]);
		if (!join)
			return (ft_putendl_fd(ERR_MAL, 2), 1);
		(free(env->value), env->value = NULL);
		env->value = join;
		free_2d_char(splited);
	}
	else
	{
		node = env_new(ft_substr(splited[0], 0, strlen), splited[1]);
		env->next = node;
		(free(splited[0]), free(splited));
	}
	return (0);
}

int	all_alpha_num(char *str)
{
	int	i;
	int	len;

	i = 0;
	if (!ft_isalpha(*str))
		return (0);
	len = ft_strlen(str);
	while (i < len - 1)
	{
		if (!ft_isalnum(*(str + i)))
			return (0);
		i++;
	}
	if (*(str + i) == '+' || ft_isalnum(*(str + i)))
		return (1);
	return (0);
}

void	add_export(t_shell *data, t_env **env, char **to_add)
{
	char	**splited;
	int		i;

	i = -1;
	while (to_add[++i])
	{
		splited = ft_split(to_add[i], '=');
		if (!splited)
			return (data->status = 1, ft_putendl_fd(ERR_MAL, 2));
		else if (!splited[0] || !ft_strlen(splited[0]) \
		|| !all_alpha_num(splited[0]))
		{
			if (!i)
				(ft_putendl_fd("not a valid identifier", 2), data->status = 1);
			return ;
		}
		if (splited[0][ft_strlen(splited[0]) - 1] == '+')
		{
			if (append(*env, splited))
				return (data->status = 1, (void)i);
		}
		else
			(new_var(*env, splited), free(splited));
	}
	data->status = 0;
}
