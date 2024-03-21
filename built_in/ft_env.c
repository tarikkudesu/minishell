/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:26:43 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/21 14:18:43 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_shell *data, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->name && tmp->value)
			printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	data->status = 0;
	if (data->cmd_nbr > 1)
		exit(0);
}
