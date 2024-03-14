/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 23:17:02 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/14 13:17:06 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(t_shell *data)
{
	char	*position;

	position = getcwd(NULL, 0);
	if (!position)
	{
		throw_error(strerror(errno));
		data->status = 1;
	}
	ft_putendl_fd(position, 1);
}

// int	main(void)
// {
// 	ft_pwd();
// }