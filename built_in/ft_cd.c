/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:10:05 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/11 00:28:11 by ooulcaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd(char *path)
{
	struct stat	st;

	if (!path || !ft_strcmp(path, "~"))
	{
		if (chdir("/Users/ooulcaid") < 0)
			ft_throw(strerror(errno), 1);
	}
	else if (stat(path, &st) < 0)
		ft_throw("No such file or directory", 1);
	else if (!S_ISDIR(st.st_mode))
		(printf("minishell: cd: %s: Not a directory\n", path), exit(1));
	else if (chdir(path) < 0)
		ft_throw(strerror(errno), 1);
}
