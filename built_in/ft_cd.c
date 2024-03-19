/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulcaid <ooulcaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:10:05 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/18 23:29:32 by ooulcaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_if(int processes, int status)
{
	if (processes > 1)
		exit (status);
}

void	ft_cd(t_shell *data, char *path)
{
	struct stat	st;

	if (!path || !ft_strcmp(path, "~"))
	{
		if (chdir("/Users/ooulcaid") < 0)
		{
			(perror("ERROR_CHANIGNG_DIRECTORY"), data->status = 1);
			return (exit_if(data->number_of_commands, 1));
		}
	}
	else if (stat(path, &st) < 0)
	{
		(perror("minishel "), data->status = 1);
		return (exit_if(data->number_of_commands, 1));
	}
	else if (!S_ISDIR(st.st_mode))
	{
		(printf("minishell: cd: %s: Not a directory\n", path),
			data->status = 1);
		return (exit_if(data->number_of_commands, 1));
	}
	else if (chdir(path) < 0)
		(perror("ERROR_CHANIGNG_DIRECTORY"), data->status = 1);
	data->status = 0;
	return (exit_if(data->number_of_commands, 0));
}
