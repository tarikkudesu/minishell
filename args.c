/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:43:06 by tamehri           #+#    #+#             */
/*   Updated: 2024/03/15 13:32:08 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// char	**get_args(t_tokens *branch)
// {
// 	char	*arg;
// 	char	*to_free;

// 	to_free = NULL;
// 	arg = NULL;
// 	while (branch)
// 	{
// 		if (branch->class == WORD)
// 		{
// 			to_free = arg;
// 			arg = ft_strjoin(branch->string, " ");
// 			if (!arg)
// 				return (NULL);
// 			if (to_free)
// 				free(to_free);
// 		}
// 		branch = branch->right;
// 	}
// 	return (ft_split(arg, ' '));
// }

