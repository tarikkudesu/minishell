/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:52:27 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/21 22:18:03 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	append(t_shell *data, t_env *env, char *name, char *value)
{
	t_env	*node;
	char	*join;

	while (env && ft_strcmp(name, env->name))
		env = env->next;
	if (env)
	{
		join = ft_strjoin(env->value, value);
		if (!join)
			return (ft_putendl_fd(ERR_MAL, 2), 1);
		(free(env->value), free(name), free(value));
		env->value = join;
	}
	else
	{
		node = env_new(name, value);
		if (!node)
			return(ft_putendl_fd(ERR_MAL, 2), 1);
		env_add_back(&data->env_list, node);
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

void	export_one(t_shell *data, char *name, char *value)
{
	t_env	*node;

	if (name[ft_strlen(name) - 1] == '+' && !value)
		return (free(name), ft_putendl_fd("not a valid identifierrrr", 2));
	if (name[ft_strlen(name) - 1] == '+' )
	{
		puts("lhih");
		append(data, data->env_list, ft_substr(name, 0, ft_strlen(name) - 1), value);
		free(name);
	}
	else
	{
		puts("hna");
		node = env_new(name, value);
		if (!node)
			return (ft_putendl_fd(ERR_MAL, 2));
		env_add_back(&data->env_list, node);
	}
}

void	add_export(t_shell *data, char **to_add)
{
	int		i;
	char	*name;
	char	*value;
	char	*help;

	i = -1;
	while (to_add[++i])
	{
		help = ft_strchr(to_add[i], '=');
		if (!help && !all_alpha_num(to_add[i]))
			(ft_putendl_fd("not a valid identifier", 2));
		else
		{
			if (!help)
			{
				name = ft_strdup(to_add[i]);
				value = NULL;
				export_one(data, name, value);
			}
			else
			{
				name = ft_substr(to_add[i], 0, help - to_add[i]);
				if (name && !all_alpha_num(name))
					(ft_putendl_fd("not a valid identifierrr", 2));
				value = ft_strdup(help + 1);
				export_one(data, name, value);
			}
		}
		
	}
}
