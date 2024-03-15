/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 23:17:02 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/14 23:59:07 by ooulcaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(t_shell *data)
{
	char	*position;

	position = getcwd(NULL, 0);
	if (!position)
		ft_throw(strerror(errno), 1);
	ft_putendl_fd(position, 1);
	data->status = 0;
}

// int	main(void)
// {
// 	ft_pwd();
// }