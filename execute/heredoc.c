/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 09:56:24 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/09 18:42:47 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	herdoc_red(char *eof, int input, int output)
{
	int		fd;
	char	*line;

	fd = open(".tmp", O_WRONLY | O_CREAT, 0644);
	if (fd < fd)
		ft_throw("ERROR_OPEN_HERDOC");
	while (1)
	{
		line = get_next_line(1);
		if (!line || !ft_strcmp(line, eof))
			break ;
		write(fd, line, ft_strlen(line));
		(free(line), line = NULL);
	}
	if (unlink(".tmp") < 0)
		ft_throw("ERRON_UNLINK_HERDOC");
	if (dup2(fd, input) < 0 || dup2(output, STDOUT_FILENO))
		ft_throw("ERROR_DUP2_HERDOC");
}
