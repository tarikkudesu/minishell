/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:26:43 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/14 15:25:10 by ooulcaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_shell *data, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->name)
			printf("%s", tmp->name);
		if (tmp->value)
			printf("\"=%s\"", tmp->value);
		printf("\n");
		tmp = tmp->next;
	}
	data->status = 0;
}
