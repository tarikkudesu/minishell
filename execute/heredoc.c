/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 09:56:24 by ooulcaid          #+#    #+#             */
/*   Updated: 2024/03/09 19:18:42 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	heredoc(char *del)
{
	int		fd;
	int		fd2;
	char	*line;

	fd = open(".tmp", O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		ft_throw("ERROR_OPEN_HERDOC");
	fd2 = open(".tmp", O_WRONLY | O_CREAT, 0644);
	if (fd2 < 0) 
		ft_throw("ERROR_OPEN_HERDOC");
	if (unlink(".tmp") < 0)
		ft_throw("ERRON_UNLINK_HERDOC");
	while (1)
	{
		line = get_next_line(1);
		if (!line || !ft_strcmp(line, del))
			break ;
		write(fd, line, ft_strlen(line));
		(free(line), line = NULL);
	}
	close(fd);
	return(fd2);
}
