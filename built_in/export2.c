/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:52:27 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/23 16:08:59 by ooulcaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	new_var(t_shell *data, char *name, char *value)
{
	t_env	*node;
	t_env	*tmp;

	if (name && !ft_strcmp(name, "_"))
		return (my_free(name), my_free(value));
	tmp = data->env_list;
	while (tmp && ft_strcmp(name, tmp->name))
		tmp = tmp->next;
	if (!tmp)
	{
		node = env_new(name, value);
		if (!node)
			return (ft_putendl_fd(ERR_MAL, 2));
		env_add_back(&data->env_list, node);
	}
	else
	{
		if (tmp && tmp->value && value)
			(free(tmp->value), tmp->value = value);
		free(name);
	}
}

int	append(t_shell *data, t_env *env, char *name, char *value)
{
	char	*join;

	if (name && !ft_strcmp(name, "_"))
		return (my_free(name), my_free(value), 0);
	while (env && ft_strcmp(name, env->name))
		env = env->next;
	if (env)
	{
		if (!env->value)
			env->value = value;
		else
		{
			join = ft_strjoin(env->value, value);
			if (!join)
				return (ft_putendl_fd(ERR_MAL, 2), 1);
			(free(env->value), free(name), free(value));
			env->value = join;
		}
	}
	else
		new_var(data, name, value);
	return (0);
}

int	all_alpha_num(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (str[i] && str[i + 1])
	{
		if (!ft_isalnum(str[i + 1]) && str[i + 1] != '_')
			return (0);
		i++;
	}
	return (!str[i + 1] || str[i + 1] == '+' || ft_isalnum(str[i + 1]));
}

void	export_one(t_shell *data, char *name, char *value)
{
	char	*name_env;

	if (name[ft_strlen(name) - 1] == '+' )
	{
		name_env = ft_substr(name, 0, ft_strlen(name) - 1);
		if (!name_env)
			return (free(name), free(value), ft_putendl_fd(ERR_MAL, 2));
		free(name);
		if (!all_alpha_num(name_env))
			return (free(name_env), free(value), data->status = 1, \
			ft_putendl_fd(ERR_NOT_VALID, 2));
		append(data, data->env_list, name_env, value);
	}
	else
	{
		if (!all_alpha_num(name))
			return (free(name), free(value), data->status = 1, \
			ft_putendl_fd(ERR_NOT_VALID, 2));
		new_var(data, name, value);
	}
}

void	add_export(t_shell *data, char **to_add)
{
	int		i;
	char	*name;
	char	*help;

	i = -1;
	while (to_add[++i])
	{
		help = ft_strchr(to_add[i], '=');
		if (!help && all_alpha_num(to_add[i]))
			new_var(data, ft_strdup(to_add[i]), NULL);
		else if (!help && !all_alpha_num(to_add[i]))
			(ft_putendl_fd(ERR_NOT_VALID, 2), data->status = 1);
		else
		{
			name = ft_substr(to_add[i], 0, help - to_add[i]);
			if (!name)
				return (ft_putendl_fd(ERR_MAL, 2));
			if (!ft_isalpha(*name) && *name != '_')
				(free(name), ft_putendl_fd(ERR_NOT_VALID, 2), \
					data->status = 1);
			else
				export_one(data, name, ft_strdup(help + 1));
		}
	}
}
